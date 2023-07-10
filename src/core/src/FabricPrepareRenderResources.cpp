#include "cesium/omniverse/FabricPrepareRenderResources.h"

#include "cesium/omniverse/Context.h"
#include "cesium/omniverse/FabricGeometry.h"
#include "cesium/omniverse/FabricMaterial.h"
#include "cesium/omniverse/FabricResourceManager.h"
#include "cesium/omniverse/FabricTexture.h"
#include "cesium/omniverse/GeospatialUtil.h"
#include "cesium/omniverse/GltfUtil.h"
#include "cesium/omniverse/OmniTileset.h"
#include "cesium/omniverse/UsdUtil.h"

#ifdef CESIUM_OMNI_MSVC
#pragma push_macro("OPAQUE")
#undef OPAQUE
#endif

#include <Cesium3DTilesSelection/GltfUtilities.h>
#include <Cesium3DTilesSelection/Tile.h>
#include <Cesium3DTilesSelection/Tileset.h>
#include <CesiumAsync/AsyncSystem.h>
#include <omni/ui/ImageProvider/DynamicTextureProvider.h>

namespace cesium::omniverse {

namespace {

template <typename T> size_t getIndexFromRef(const std::vector<T>& vector, const T& item) {
    return static_cast<size_t>(&item - vector.data());
};

struct ImageryLoadThreadResult {
    std::shared_ptr<FabricTexture> texture;
};

struct ImageryRenderResources {
    std::shared_ptr<FabricTexture> texture;
};

struct TileLoadThreadResult {
    glm::dmat4 tileTransform;
    bool hasImagery;
};

struct MeshInfo {
    const int64_t tilesetId;
    const glm::dmat4 ecefToUsdTransform;
    const glm::dmat4 gltfToEcefTransform;
    const glm::dmat4 nodeTransform;
    const uint64_t meshId;
    const uint64_t primitiveId;
    const bool smoothNormals;
};

std::vector<MeshInfo>
gatherMeshes(const OmniTileset& tileset, const glm::dmat4& tileTransform, const CesiumGltf::Model& model) {
    CESIUM_TRACE("FabricPrepareRenderResources::gatherMeshes");
    const auto tilesetId = tileset.getTilesetId();

    const auto smoothNormals = tileset.getSmoothNormals();

    const auto georeferenceOrigin = GeospatialUtil::convertGeoreferenceToCartographic(tileset.getGeoreference());
    const auto ecefToUsdTransform = UsdUtil::computeEcefToUsdTransformForPrim(georeferenceOrigin, tileset.getPath());

    auto gltfToEcefTransform = Cesium3DTilesSelection::GltfUtilities::applyRtcCenter(model, tileTransform);
    gltfToEcefTransform = Cesium3DTilesSelection::GltfUtilities::applyGltfUpAxisTransform(model, gltfToEcefTransform);

    std::vector<MeshInfo> meshes;

    model.forEachPrimitiveInScene(
        -1,
        [tilesetId, &ecefToUsdTransform, &gltfToEcefTransform, smoothNormals, &meshes](
            const CesiumGltf::Model& gltf,
            [[maybe_unused]] const CesiumGltf::Node& node,
            const CesiumGltf::Mesh& mesh,
            const CesiumGltf::MeshPrimitive& primitive,
            const glm::dmat4& transform) {
            const auto meshId = getIndexFromRef(gltf.meshes, mesh);
            const auto primitiveId = getIndexFromRef(mesh.primitives, primitive);
            meshes.emplace_back(MeshInfo{
                tilesetId,
                ecefToUsdTransform,
                gltfToEcefTransform,
                transform,
                meshId,
                primitiveId,
                smoothNormals,
            });
        });

    return meshes;
}

std::vector<FabricMesh>
acquireFabricMeshes(const CesiumGltf::Model& model, const std::vector<MeshInfo>& meshes, bool hasImagery) {
    CESIUM_TRACE("FabricPrepareRenderResources::acquireFabricMeshes");
    std::vector<FabricMesh> fabricMeshes;
    fabricMeshes.reserve(meshes.size());

    auto& FabricResourceManager = FabricResourceManager::getInstance();

    for (const auto& mesh : meshes) {
        auto& fabricMesh = fabricMeshes.emplace_back();

        const auto& primitive = model.meshes[mesh.meshId].primitives[mesh.primitiveId];
        const auto fabricGeometry =
            FabricResourceManager.acquireGeometry(model, primitive, mesh.smoothNormals, hasImagery);
        fabricMesh.geometry = fabricGeometry;

        if (fabricGeometry->getGeometryDefinition().hasMaterial()) {
            const auto fabricMaterial = FabricResourceManager.acquireMaterial(model, primitive, hasImagery);
            fabricMesh.material = fabricMaterial;

            const auto materialInfo = GltfUtil::getMaterialInfo(model, primitive);
            fabricMesh.materialInfo = materialInfo;

            if (fabricMaterial->getMaterialDefinition().hasBaseColorTexture() &&
                materialInfo.baseColorTexture.has_value()) {
                const auto fabricTexture = FabricResourceManager.acquireTexture();
                fabricMesh.baseColorTexture = fabricTexture;
            }
        }
    }

    return fabricMeshes;
}

void setFabricMeshes(
    const CesiumGltf::Model& model,
    const std::vector<MeshInfo>& meshes,
    std::vector<FabricMesh>& fabricMeshes,
    bool hasImagery) {
    CESIUM_TRACE("FabricPrepareRenderResources::setFabricMeshes");
    for (size_t i = 0; i < meshes.size(); i++) {
        const auto& meshInfo = meshes[i];
        const auto& primitive = model.meshes[meshInfo.meshId].primitives[meshInfo.primitiveId];

        auto& mesh = fabricMeshes[i];
        auto& geometry = mesh.geometry;
        auto& material = mesh.material;
        auto& baseColorTexture = mesh.baseColorTexture;
        auto& materialInfo = mesh.materialInfo;

        geometry->setGeometry(
            meshInfo.tilesetId,
            meshInfo.ecefToUsdTransform,
            meshInfo.gltfToEcefTransform,
            meshInfo.nodeTransform,
            model,
            primitive,
            meshInfo.smoothNormals,
            hasImagery);

        if (material != nullptr) {
            material->setMaterial(meshInfo.tilesetId, materialInfo);
            geometry->setMaterial(material);

            if (baseColorTexture != nullptr && materialInfo.baseColorTexture.has_value()) {
                const auto baseColorTextureImage = GltfUtil::getBaseColorTextureImage(model, primitive);
                baseColorTexture->setImage(*baseColorTextureImage);
                material->setBaseColorTexture(baseColorTexture, materialInfo.baseColorTexture.value());
            }
        }
    }
}

} // namespace

FabricPrepareRenderResources::FabricPrepareRenderResources(const OmniTileset& tileset)
    : _tileset(tileset) {}

CesiumAsync::Future<Cesium3DTilesSelection::TileLoadResultAndRenderResources>
FabricPrepareRenderResources::prepareInLoadThread(
    const CesiumAsync::AsyncSystem& asyncSystem,
    Cesium3DTilesSelection::TileLoadResult&& tileLoadResult,
    const glm::dmat4& transform,
    [[maybe_unused]] const std::any& rendererOptions) {
    const auto pModel = std::get_if<CesiumGltf::Model>(&tileLoadResult.contentKind);
    if (!pModel) {
        return asyncSystem.createResolvedFuture(
            Cesium3DTilesSelection::TileLoadResultAndRenderResources{std::move(tileLoadResult), nullptr});
    }

    const auto hasImagery = tileLoadResult.rasterOverlayDetails.has_value();

    return asyncSystem.createResolvedFuture(Cesium3DTilesSelection::TileLoadResultAndRenderResources{
        std::move(tileLoadResult),
        new TileLoadThreadResult{
            transform,
            hasImagery,
        },
    });
}

void* FabricPrepareRenderResources::prepareInMainThread(Cesium3DTilesSelection::Tile& tile, void* pLoadThreadResult) {
    if (!pLoadThreadResult) {
        return nullptr;
    }

    std::unique_ptr<TileLoadThreadResult> pTileLoadThreadResult{
        reinterpret_cast<TileLoadThreadResult*>(pLoadThreadResult)};

    const auto& tileTransform = pTileLoadThreadResult->tileTransform;
    const auto hasImagery = pTileLoadThreadResult->hasImagery;

    const auto& content = tile.getContent();
    auto pRenderContent = content.getRenderContent();
    if (!pRenderContent) {
        return nullptr;
    }

    const auto& model = pRenderContent->getModel();

    auto meshes = gatherMeshes(_tileset, tileTransform, model);
    auto fabricMeshes = acquireFabricMeshes(model, meshes, hasImagery);

    setFabricMeshes(model, meshes, fabricMeshes, hasImagery);

    return new TileRenderResources{
        tileTransform,
        std::move(fabricMeshes),
    };
}

void FabricPrepareRenderResources::free(
    [[maybe_unused]] Cesium3DTilesSelection::Tile& tile,
    void* pLoadThreadResult,
    void* pMainThreadResult) noexcept {
    if (pLoadThreadResult) {
        const auto pTileLoadThreadResult = reinterpret_cast<TileLoadThreadResult*>(pLoadThreadResult);
        delete pTileLoadThreadResult;
    }

    if (pMainThreadResult) {
        const auto pTileRenderResources = reinterpret_cast<TileRenderResources*>(pMainThreadResult);
        auto& FabricResourceManager = FabricResourceManager::getInstance();

        for (const auto& mesh : pTileRenderResources->fabricMeshes) {
            auto& geometry = mesh.geometry;
            auto& material = mesh.material;
            auto& baseColorTexture = mesh.baseColorTexture;

            assert(geometry != nullptr);

            FabricResourceManager.releaseGeometry(geometry);

            if (material != nullptr) {
                FabricResourceManager.releaseMaterial(material);
            }

            if (baseColorTexture != nullptr) {
                FabricResourceManager.releaseTexture(baseColorTexture);
            }
        }

        delete pTileRenderResources;
    }
}

void* FabricPrepareRenderResources::prepareRasterInLoadThread(
    CesiumGltf::ImageCesium& image,
    [[maybe_unused]] const std::any& rendererOptions) {
    auto texture = FabricResourceManager::getInstance().acquireTexture();
    texture->setImage(image);
    return new ImageryLoadThreadResult{texture};
}

void* FabricPrepareRenderResources::prepareRasterInMainThread(
    [[maybe_unused]] Cesium3DTilesSelection::RasterOverlayTile& rasterTile,
    void* pLoadThreadResult) {
    if (!pLoadThreadResult) {
        return nullptr;
    }

    std::unique_ptr<ImageryLoadThreadResult> pImageryLoadThreadResult{
        reinterpret_cast<ImageryLoadThreadResult*>(pLoadThreadResult)};

    auto texture = pImageryLoadThreadResult->texture;

    return new ImageryRenderResources{texture};
}

void FabricPrepareRenderResources::freeRaster(
    [[maybe_unused]] const Cesium3DTilesSelection::RasterOverlayTile& rasterTile,
    void* pLoadThreadResult,
    void* pMainThreadResult) noexcept {

    if (pLoadThreadResult) {
        const auto pImageryLoadThreadResult = reinterpret_cast<ImageryLoadThreadResult*>(pLoadThreadResult);
        const auto texture = pImageryLoadThreadResult->texture;
        FabricResourceManager::getInstance().releaseTexture(texture);
        delete pImageryLoadThreadResult;
    }

    if (pMainThreadResult) {
        const auto pImageryRenderResources = reinterpret_cast<ImageryRenderResources*>(pMainThreadResult);
        const auto texture = pImageryRenderResources->texture;
        FabricResourceManager::getInstance().releaseTexture(texture);
        delete pImageryRenderResources;
    }
}

void FabricPrepareRenderResources::attachRasterInMainThread(
    const Cesium3DTilesSelection::Tile& tile,
    int32_t overlayTextureCoordinateID,
    [[maybe_unused]] const Cesium3DTilesSelection::RasterOverlayTile& rasterTile,
    void* pMainThreadRendererResources,
    const glm::dvec2& translation,
    const glm::dvec2& scale) {

    auto pImageryRenderResources = reinterpret_cast<ImageryRenderResources*>(pMainThreadRendererResources);
    if (!pImageryRenderResources) {
        return;
    }

    const auto texture = pImageryRenderResources->texture;

    auto& content = tile.getContent();
    auto pRenderContent = content.getRenderContent();
    if (!pRenderContent) {
        return;
    }

    auto pTileRenderResources = reinterpret_cast<TileRenderResources*>(pRenderContent->getRenderResources());
    if (!pTileRenderResources) {
        return;
    }

    for (const auto& mesh : pTileRenderResources->fabricMeshes) {
        auto& material = mesh.material;
        if (material != nullptr) {
            const auto textureInfo = TextureInfo{
                translation,
                0.0,
                scale,
                static_cast<uint64_t>(overlayTextureCoordinateID),
                CesiumGltf::Sampler::WrapS::CLAMP_TO_EDGE,
                CesiumGltf::Sampler::WrapT::CLAMP_TO_EDGE,
                false,
            };

            // Replace the original base color texture with the imagery
            material->setBaseColorTexture(texture, textureInfo);
        }
    }
}

void FabricPrepareRenderResources::detachRasterInMainThread(
    const Cesium3DTilesSelection::Tile& tile,
    [[maybe_unused]] int32_t overlayTextureCoordinateID,
    [[maybe_unused]] const Cesium3DTilesSelection::RasterOverlayTile& rasterTile,
    [[maybe_unused]] void* pMainThreadRendererResources) noexcept {

    auto& content = tile.getContent();
    auto pRenderContent = content.getRenderContent();
    if (!pRenderContent) {
        return;
    }

    auto pTileRenderResources = reinterpret_cast<TileRenderResources*>(pRenderContent->getRenderResources());
    if (!pTileRenderResources) {
        return;
    }

    for (const auto& mesh : pTileRenderResources->fabricMeshes) {
        auto& material = mesh.material;
        const auto& baseColorTexture = mesh.baseColorTexture;
        const auto& materialInfo = mesh.materialInfo;

        if (material != nullptr) {
            if (baseColorTexture != nullptr && materialInfo.baseColorTexture.has_value()) {
                // Switch back to the original base color texture
                material->setBaseColorTexture(baseColorTexture, materialInfo.baseColorTexture.value());
            } else {
                material->clearBaseColorTexture();
            }
        }
    }
}

} // namespace cesium::omniverse
