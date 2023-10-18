#include "cesium/omniverse/FabricMaterial.h"

#include "cesium/omniverse/Context.h"
#include "cesium/omniverse/FabricAttributesBuilder.h"
#include "cesium/omniverse/FabricMaterialDefinition.h"
#include "cesium/omniverse/FabricResourceManager.h"
#include "cesium/omniverse/FabricUtil.h"
#include "cesium/omniverse/GltfUtil.h"
#include "cesium/omniverse/LoggerSink.h"
#include "cesium/omniverse/Tokens.h"
#include "cesium/omniverse/UsdUtil.h"

#include <omni/fabric/FabricUSD.h>
#include <spdlog/fmt/fmt.h>

namespace cesium::omniverse {

namespace {
uint64_t getImageryLayerCount(const FabricMaterialDefinition& materialDefinition) {
    uint64_t imageryLayerCount = materialDefinition.getImageryLayerCount();

    if (imageryLayerCount > FabricTokens::MAX_IMAGERY_LAYERS_COUNT) {
        CESIUM_LOG_WARN(
            "Number of imagery layers ({}) exceeds maximum imagery layer count ({}). Excess imagery layers will be "
            "ignored.",
            imageryLayerCount,
            FabricTokens::MAX_IMAGERY_LAYERS_COUNT);
    }

    imageryLayerCount = glm::min(imageryLayerCount, FabricTokens::MAX_IMAGERY_LAYERS_COUNT);

    return imageryLayerCount;
}
} // namespace

FabricMaterial::FabricMaterial(
    const omni::fabric::Path& path,
    const FabricMaterialDefinition& materialDefinition,
    const pxr::TfToken& defaultTextureAssetPathToken,
    const pxr::TfToken& defaultTransparentTextureAssetPathToken,
    long stageId)
    : _materialPath(path)
    , _materialDefinition(materialDefinition)
    , _defaultTextureAssetPathToken(defaultTextureAssetPathToken)
    , _defaultTransparentTextureAssetPathToken(defaultTransparentTextureAssetPathToken)
    , _stageId(stageId) {

    if (stageDestroyed()) {
        return;
    }

    if (materialDefinition.hasTilesetMaterial()) {
        const auto tilesetMaterialPath = FabricUtil::toFabricPath(materialDefinition.getTilesetMaterialPath());
        initializeFromExistingMaterial(tilesetMaterialPath);
    } else {
        initialize();
    }

    reset();
}

FabricMaterial::~FabricMaterial() {
    if (stageDestroyed()) {
        return;
    }

    for (const auto& path : _allPaths) {
        FabricUtil::destroyPrim(path);
    }
}

void FabricMaterial::setActive(bool active) {
    if (stageDestroyed()) {
        return;
    }

    if (!active) {
        reset();
    }
}

const omni::fabric::Path& FabricMaterial::getPath() const {
    return _materialPath;
}

const FabricMaterialDefinition& FabricMaterial::getMaterialDefinition() const {
    return _materialDefinition;
}

void FabricMaterial::initialize() {
    const auto& materialPath = _materialPath;
    createMaterial(materialPath);
    _allPaths.push_back(materialPath);

    const auto shaderPath = FabricUtil::joinPaths(materialPath, FabricTokens::Shader);
    createShader(shaderPath, materialPath);
    _shaderPaths.push_back(shaderPath);
    _allPaths.push_back(shaderPath);

    if (_materialDefinition.hasBaseColorTexture()) {
        const auto baseColorTexturePath = FabricUtil::joinPaths(materialPath, FabricTokens::base_color_texture);
        createTexture(baseColorTexturePath, shaderPath, FabricTokens::inputs_base_color_texture);
        _baseColorTexturePaths.push_back(baseColorTexturePath);
        _allPaths.push_back(baseColorTexturePath);
    }

    const auto imageryLayerCount = getImageryLayerCount(_materialDefinition);

    if (imageryLayerCount == 1) {
        const auto imageryLayerPath = FabricUtil::joinPaths(materialPath, FabricTokens::imagery_layer_n[0]);
        createTexture(imageryLayerPath, shaderPath, FabricTokens::inputs_imagery_layers_texture);
        _imageryLayerPaths.push_back({imageryLayerPath});
        _allPaths.push_back(imageryLayerPath);
    } else if (imageryLayerCount > 1) {
        const auto imageryLayerResolverPath = FabricUtil::joinPaths(materialPath, FabricTokens::imagery_layer_resolver);
        createImageryLayerResolver(
            imageryLayerResolverPath, shaderPath, FabricTokens::inputs_imagery_layers_texture, imageryLayerCount);
        _allPaths.push_back(imageryLayerResolverPath);

        _imageryLayerPaths.reserve(imageryLayerCount);
        for (uint64_t i = 0; i < imageryLayerCount; i++) {
            const auto imageryLayerPath = FabricUtil::joinPaths(materialPath, FabricTokens::imagery_layer_n[i]);
            createTexture(imageryLayerPath, imageryLayerResolverPath, FabricTokens::inputs_imagery_layer_n[i]);
            _imageryLayerPaths.push_back({imageryLayerPath});
            _allPaths.push_back(imageryLayerPath);
        }
    }

    for (const auto& path : _allPaths) {
        FabricResourceManager::getInstance().retainPath(path);
    }
}

void FabricMaterial::initializeFromExistingMaterial(const omni::fabric::Path& srcMaterialPath) {
    auto srw = UsdUtil::getFabricStageReaderWriter();

    const auto& dstMaterialPath = _materialPath;

    const auto dstPaths = FabricUtil::copyMaterial(srcMaterialPath, dstMaterialPath);

    for (const auto& dstPath : dstPaths) {
        srw.createAttribute(dstPath, FabricTokens::_cesium_tilesetId, FabricTypes::_cesium_tilesetId);
        _allPaths.push_back(dstPath);

        const auto mdlIdentifier = FabricUtil::getMdlIdentifier(dstPath);

        if (mdlIdentifier == FabricTokens::cesium_base_color_texture) {
            if (_materialDefinition.hasBaseColorTexture()) {
                // Create a base color texture node to fill the empty slot
                const auto baseColorTexturePath =
                    FabricUtil::joinPaths(dstMaterialPath, FabricTokens::base_color_texture);
                createTexture(baseColorTexturePath, dstPath, FabricTokens::inputs_base_color_texture);
                _allPaths.push_back(baseColorTexturePath);
                _baseColorTexturePaths.push_back(baseColorTexturePath);
                FabricResourceManager::getInstance().retainPath(baseColorTexturePath);
            }
        }
    }

    for (const auto& path : _allPaths) {
        FabricResourceManager::getInstance().retainPath(path);
    }
}

void FabricMaterial::createMaterial(const omni::fabric::Path& materialPath) {
    auto srw = UsdUtil::getFabricStageReaderWriter();
    srw.createPrim(materialPath);

    FabricAttributesBuilder attributes;

    attributes.addAttribute(FabricTypes::Material, FabricTokens::Material);
    attributes.addAttribute(FabricTypes::_cesium_tilesetId, FabricTokens::_cesium_tilesetId);

    attributes.createAttributes(materialPath);
}

void FabricMaterial::createShader(const omni::fabric::Path& shaderPath, const omni::fabric::Path& materialPath) {
    const auto hasVertexColors = _materialDefinition.hasVertexColors();

    auto srw = UsdUtil::getFabricStageReaderWriter();

    srw.createPrim(shaderPath);

    FabricAttributesBuilder attributes;

    // clang-format off
    // TODO: add debug_color
    attributes.addAttribute(FabricTypes::inputs_alpha_cutoff, FabricTokens::inputs_alpha_cutoff);
    attributes.addAttribute(FabricTypes::inputs_alpha_mode, FabricTokens::inputs_alpha_mode);
    attributes.addAttribute(FabricTypes::inputs_base_alpha, FabricTokens::inputs_base_alpha);
    attributes.addAttribute(FabricTypes::inputs_base_color_factor, FabricTokens::inputs_base_color_factor);
    attributes.addAttribute(FabricTypes::inputs_emissive_factor, FabricTokens::inputs_emissive_factor);
    attributes.addAttribute(FabricTypes::inputs_metallic_factor, FabricTokens::inputs_metallic_factor);
    attributes.addAttribute(FabricTypes::inputs_roughness_factor, FabricTokens::inputs_roughness_factor);
    attributes.addAttribute(FabricTypes::inputs_excludeFromWhiteMode, FabricTokens::inputs_excludeFromWhiteMode);
    attributes.addAttribute(FabricTypes::outputs_out, FabricTokens::outputs_out);
    attributes.addAttribute(FabricTypes::info_implementationSource, FabricTokens::info_implementationSource);
    attributes.addAttribute(FabricTypes::info_mdl_sourceAsset, FabricTokens::info_mdl_sourceAsset);
    attributes.addAttribute(FabricTypes::info_mdl_sourceAsset_subIdentifier, FabricTokens::info_mdl_sourceAsset_subIdentifier);
    attributes.addAttribute(FabricTypes::_paramColorSpace, FabricTokens::_paramColorSpace);
    attributes.addAttribute(FabricTypes::_sdrMetadata, FabricTokens::_sdrMetadata);
    attributes.addAttribute(FabricTypes::Shader, FabricTokens::Shader);
    attributes.addAttribute(FabricTypes::_cesium_tilesetId, FabricTokens::_cesium_tilesetId);
    // clang-format on

    if (hasVertexColors) {
        attributes.addAttribute(FabricTypes::inputs_vertex_color_name, FabricTokens::inputs_vertex_color_name);
    }

    attributes.createAttributes(shaderPath);

    srw.setArrayAttributeSize(shaderPath, FabricTokens::_paramColorSpace, 0);
    srw.setArrayAttributeSize(shaderPath, FabricTokens::_sdrMetadata, 0);

    // clang-format off
    auto inputsExcludeFromWhiteModeFabric = srw.getAttributeWr<bool>(shaderPath, FabricTokens::inputs_excludeFromWhiteMode);
    auto infoImplementationSourceFabric = srw.getAttributeWr<omni::fabric::TokenC>(shaderPath, FabricTokens::info_implementationSource);
    auto infoMdlSourceAssetFabric = srw.getAttributeWr<omni::fabric::AssetPath>(shaderPath, FabricTokens::info_mdl_sourceAsset);
    auto infoMdlSourceAssetSubIdentifierFabric = srw.getAttributeWr<omni::fabric::TokenC>(shaderPath, FabricTokens::info_mdl_sourceAsset_subIdentifier);
    // clang-format on

    *inputsExcludeFromWhiteModeFabric = false;
    *infoImplementationSourceFabric = FabricTokens::sourceAsset;
    infoMdlSourceAssetFabric->assetPath = Context::instance().getCesiumMdlPathToken();
    infoMdlSourceAssetFabric->resolvedPath = pxr::TfToken();
    *infoMdlSourceAssetSubIdentifierFabric = FabricTokens::cesium_material;

    if (hasVertexColors) {
        const auto vertexColorPrimvarNameSize = pxr::UsdTokens->vertexColor.GetString().size();
        srw.setArrayAttributeSize(shaderPath, FabricTokens::inputs_vertex_color_name, vertexColorPrimvarNameSize);
        auto vertexColorNameFabric =
            srw.getArrayAttributeWr<uint8_t>(shaderPath, FabricTokens::inputs_vertex_color_name);
        memcpy(vertexColorNameFabric.data(), pxr::UsdTokens->vertexColor.GetText(), vertexColorPrimvarNameSize);
    }

    // Connect the material terminals to the shader.
    srw.createConnection(
        materialPath,
        FabricTokens::outputs_mdl_surface,
        omni::fabric::Connection{shaderPath, FabricTokens::outputs_out});
    srw.createConnection(
        materialPath,
        FabricTokens::outputs_mdl_displacement,
        omni::fabric::Connection{shaderPath, FabricTokens::outputs_out});
    srw.createConnection(
        materialPath,
        FabricTokens::outputs_mdl_volume,
        omni::fabric::Connection{shaderPath, FabricTokens::outputs_out});
}

void FabricMaterial::createTexture(
    const omni::fabric::Path& texturePath,
    const omni::fabric::Path& shaderPath,
    const omni::fabric::Token& shaderInput) {
    auto srw = UsdUtil::getFabricStageReaderWriter();

    srw.createPrim(texturePath);

    FabricAttributesBuilder attributes;

    // clang-format off
    attributes.addAttribute(FabricTypes::inputs_offset, FabricTokens::inputs_offset);
    attributes.addAttribute(FabricTypes::inputs_rotation, FabricTokens::inputs_rotation);
    attributes.addAttribute(FabricTypes::inputs_scale, FabricTokens::inputs_scale);
    attributes.addAttribute(FabricTypes::inputs_tex_coord_index, FabricTokens::inputs_tex_coord_index);
    attributes.addAttribute(FabricTypes::inputs_texture, FabricTokens::inputs_texture);
    attributes.addAttribute(FabricTypes::inputs_wrap_s, FabricTokens::inputs_wrap_s);
    attributes.addAttribute(FabricTypes::inputs_wrap_t, FabricTokens::inputs_wrap_t);
    attributes.addAttribute(FabricTypes::inputs_excludeFromWhiteMode, FabricTokens::inputs_excludeFromWhiteMode);
    attributes.addAttribute(FabricTypes::outputs_out, FabricTokens::outputs_out);
    attributes.addAttribute(FabricTypes::info_implementationSource, FabricTokens::info_implementationSource);
    attributes.addAttribute(FabricTypes::info_mdl_sourceAsset, FabricTokens::info_mdl_sourceAsset);
    attributes.addAttribute(FabricTypes::info_mdl_sourceAsset_subIdentifier, FabricTokens::info_mdl_sourceAsset_subIdentifier);
    attributes.addAttribute(FabricTypes::_paramColorSpace, FabricTokens::_paramColorSpace);
    attributes.addAttribute(FabricTypes::_sdrMetadata, FabricTokens::_sdrMetadata);
    attributes.addAttribute(FabricTypes::Shader, FabricTokens::Shader);
    attributes.addAttribute(FabricTypes::_cesium_tilesetId, FabricTokens::_cesium_tilesetId);
    // clang-format on

    attributes.createAttributes(texturePath);

    // _paramColorSpace is an array of pairs: [texture_parameter_token, color_space_enum], [texture_parameter_token, color_space_enum], ...
    srw.setArrayAttributeSize(texturePath, FabricTokens::_paramColorSpace, 2);
    srw.setArrayAttributeSize(texturePath, FabricTokens::_sdrMetadata, 0);

    // clang-format off
    auto inputsExcludeFromWhiteModeFabric = srw.getAttributeWr<bool>(texturePath, FabricTokens::inputs_excludeFromWhiteMode);
    auto infoImplementationSourceFabric = srw.getAttributeWr<omni::fabric::TokenC>(texturePath, FabricTokens::info_implementationSource);
    auto infoMdlSourceAssetFabric = srw.getAttributeWr<omni::fabric::AssetPath>(texturePath, FabricTokens::info_mdl_sourceAsset);
    auto infoMdlSourceAssetSubIdentifierFabric = srw.getAttributeWr<omni::fabric::TokenC>(texturePath, FabricTokens::info_mdl_sourceAsset_subIdentifier);
    auto paramColorSpaceFabric = srw.getArrayAttributeWr<omni::fabric::TokenC>(texturePath, FabricTokens::_paramColorSpace);
    // clang-format on

    *inputsExcludeFromWhiteModeFabric = false;
    *infoImplementationSourceFabric = FabricTokens::sourceAsset;
    infoMdlSourceAssetFabric->assetPath = Context::instance().getCesiumMdlPathToken();
    infoMdlSourceAssetFabric->resolvedPath = pxr::TfToken();
    *infoMdlSourceAssetSubIdentifierFabric = FabricTokens::cesium_texture_lookup;
    paramColorSpaceFabric[0] = FabricTokens::inputs_texture;
    paramColorSpaceFabric[1] = FabricTokens::_auto;

    // Create connection from shader to texture.
    srw.createConnection(shaderPath, shaderInput, omni::fabric::Connection{texturePath, FabricTokens::outputs_out});
}

void FabricMaterial::createImageryLayerResolver(
    const omni::fabric::Path& imageryLayerResolverPath,
    const omni::fabric::Path& shaderPath,
    const omni::fabric::Token& shaderInput,
    uint64_t imageryLayerCount) {
    auto srw = UsdUtil::getFabricStageReaderWriter();

    srw.createPrim(imageryLayerResolverPath);

    FabricAttributesBuilder attributes;

    // clang-format off
    attributes.addAttribute(FabricTypes::inputs_imagery_layers_count, FabricTokens::inputs_imagery_layers_count);
    attributes.addAttribute(FabricTypes::inputs_excludeFromWhiteMode, FabricTokens::inputs_excludeFromWhiteMode);
    attributes.addAttribute(FabricTypes::outputs_out, FabricTokens::outputs_out);
    attributes.addAttribute(FabricTypes::info_implementationSource, FabricTokens::info_implementationSource);
    attributes.addAttribute(FabricTypes::info_mdl_sourceAsset, FabricTokens::info_mdl_sourceAsset);
    attributes.addAttribute(FabricTypes::info_mdl_sourceAsset_subIdentifier, FabricTokens::info_mdl_sourceAsset_subIdentifier);
    attributes.addAttribute(FabricTypes::_sdrMetadata, FabricTokens::_sdrMetadata);
    attributes.addAttribute(FabricTypes::Shader, FabricTokens::Shader);
    attributes.addAttribute(FabricTypes::_cesium_tilesetId, FabricTokens::_cesium_tilesetId);
    // clang-format on

    attributes.createAttributes(imageryLayerResolverPath);

    // clang-format off
    auto imageryLayerCountFabric = srw.getAttributeWr<int>(imageryLayerResolverPath, FabricTokens::inputs_imagery_layers_count);
    auto inputsExcludeFromWhiteModeFabric = srw.getAttributeWr<bool>(imageryLayerResolverPath, FabricTokens::inputs_excludeFromWhiteMode);
    auto infoImplementationSourceFabric = srw.getAttributeWr<omni::fabric::TokenC>(imageryLayerResolverPath, FabricTokens::info_implementationSource);
    auto infoMdlSourceAssetFabric = srw.getAttributeWr<omni::fabric::AssetPath>(imageryLayerResolverPath, FabricTokens::info_mdl_sourceAsset);
    auto infoMdlSourceAssetSubIdentifierFabric = srw.getAttributeWr<omni::fabric::TokenC>(imageryLayerResolverPath, FabricTokens::info_mdl_sourceAsset_subIdentifier);
    // clang-format on

    *imageryLayerCountFabric = static_cast<int>(imageryLayerCount);
    *inputsExcludeFromWhiteModeFabric = false;
    *infoImplementationSourceFabric = FabricTokens::sourceAsset;
    infoMdlSourceAssetFabric->assetPath = Context::instance().getCesiumMdlPathToken();
    infoMdlSourceAssetFabric->resolvedPath = pxr::TfToken();
    *infoMdlSourceAssetSubIdentifierFabric = FabricTokens::cesium_imagery_layer_resolver;

    // Create connection to shader
    srw.createConnection(
        shaderPath, shaderInput, omni::fabric::Connection{imageryLayerResolverPath, FabricTokens::outputs_out});
}

void FabricMaterial::reset() {
    clearMaterial();
    clearBaseColorTexture();
    clearImageryLayers();
}

void FabricMaterial::setMaterial(int64_t tilesetId, const MaterialInfo& materialInfo) {
    if (stageDestroyed()) {
        return;
    }

    auto srw = UsdUtil::getFabricStageReaderWriter();

    for (auto& shaderPath : _shaderPaths) {
        setShaderValues(shaderPath, materialInfo);
    }

    for (const auto& path : _allPaths) {
        FabricUtil::setTilesetId(path, tilesetId);
    }
}

void FabricMaterial::setBaseColorTexture(
    const pxr::TfToken& textureAssetPathToken,
    const TextureInfo& textureInfo,
    uint64_t texcoordIndex) {
    if (stageDestroyed()) {
        return;
    }

    for (auto& baseColorTexturePath : _baseColorTexturePaths) {
        setTextureValues(baseColorTexturePath, textureAssetPathToken, textureInfo, texcoordIndex);
    }
}

void FabricMaterial::setImageryLayer(
    const pxr::TfToken& textureAssetPathToken,
    const TextureInfo& textureInfo,
    uint64_t texcoordIndex,
    uint64_t imageryIndex) {
    if (stageDestroyed()) {
        return;
    }

    if (imageryIndex >= _imageryLayerPaths.size()) {
        return;
    }

    for (auto& imageryLayerPath : _imageryLayerPaths[imageryIndex]) {
        setTextureValues(imageryLayerPath, textureAssetPathToken, textureInfo, texcoordIndex);
    }
}

void FabricMaterial::clearMaterial() {
    setMaterial(NO_TILESET_ID, GltfUtil::getDefaultMaterialInfo());
}

void FabricMaterial::clearBaseColorTexture() {
    setBaseColorTexture(_defaultTextureAssetPathToken, GltfUtil::getDefaultTextureInfo(), 0);
}

void FabricMaterial::clearImageryLayer(uint64_t imageryIndex) {
    setImageryLayer(_defaultTransparentTextureAssetPathToken, GltfUtil::getDefaultTextureInfo(), 0, imageryIndex);
}

void FabricMaterial::clearImageryLayers() {
    for (uint64_t i = 0; i < _imageryLayerPaths.size(); i++) {
        clearImageryLayer(i);
    }
}

void FabricMaterial::setShaderValues(const omni::fabric::Path& shaderPath, const MaterialInfo& materialInfo) {
    auto srw = UsdUtil::getFabricStageReaderWriter();

    auto alphaCutoffFabric = srw.getAttributeWr<float>(shaderPath, FabricTokens::inputs_alpha_cutoff);
    auto alphaModeFabric = srw.getAttributeWr<int>(shaderPath, FabricTokens::inputs_alpha_mode);
    auto baseAlphaFabric = srw.getAttributeWr<float>(shaderPath, FabricTokens::inputs_base_alpha);
    auto baseColorFactorFabric = srw.getAttributeWr<pxr::GfVec3f>(shaderPath, FabricTokens::inputs_base_color_factor);
    auto emissiveFactorFabric = srw.getAttributeWr<pxr::GfVec3f>(shaderPath, FabricTokens::inputs_emissive_factor);
    auto metallicFactorFabric = srw.getAttributeWr<float>(shaderPath, FabricTokens::inputs_metallic_factor);
    auto roughnessFactorFabric = srw.getAttributeWr<float>(shaderPath, FabricTokens::inputs_roughness_factor);

    *alphaCutoffFabric = static_cast<float>(materialInfo.alphaCutoff);
    *alphaModeFabric = materialInfo.alphaMode;
    *baseAlphaFabric = static_cast<float>(materialInfo.baseAlpha);
    *baseColorFactorFabric = UsdUtil::glmToUsdVector(glm::fvec3(materialInfo.baseColorFactor));
    *emissiveFactorFabric = UsdUtil::glmToUsdVector(glm::fvec3(materialInfo.emissiveFactor));
    *metallicFactorFabric = static_cast<float>(materialInfo.metallicFactor);
    *roughnessFactorFabric = static_cast<float>(materialInfo.roughnessFactor);
}

void FabricMaterial::setTextureValues(
    const omni::fabric::Path& texturePath,
    const pxr::TfToken& textureAssetPathToken,
    const TextureInfo& textureInfo,
    uint64_t texcoordIndex) {

    if (texcoordIndex >= FabricTokens::MAX_PRIMVAR_ST_COUNT) {
        return;
    }

    auto srw = UsdUtil::getFabricStageReaderWriter();

    auto offset = textureInfo.offset;
    auto rotation = textureInfo.rotation;
    auto scale = textureInfo.scale;

    if (!textureInfo.flipVertical) {
        // gltf/pbr.mdl does texture transform math in glTF coordinates (top-left origin), so we needed to convert
        // the translation and scale parameters to work in that space. This doesn't handle rotation yet because we
        // haven't needed it for imagery layers.
        offset = {offset.x, 1.0 - offset.y - scale.y};
        scale = {scale.x, scale.y};
    }

    auto textureFabric = srw.getAttributeWr<omni::fabric::AssetPath>(texturePath, FabricTokens::inputs_texture);
    auto texCoordIndexFabric = srw.getAttributeWr<int>(texturePath, FabricTokens::inputs_tex_coord_index);
    auto wrapSFabric = srw.getAttributeWr<int>(texturePath, FabricTokens::inputs_wrap_s);
    auto wrapTFabric = srw.getAttributeWr<int>(texturePath, FabricTokens::inputs_wrap_t);
    auto offsetFabric = srw.getAttributeWr<pxr::GfVec2f>(texturePath, FabricTokens::inputs_offset);
    auto rotationFabric = srw.getAttributeWr<float>(texturePath, FabricTokens::inputs_rotation);
    auto scaleFabric = srw.getAttributeWr<pxr::GfVec2f>(texturePath, FabricTokens::inputs_scale);

    textureFabric->assetPath = textureAssetPathToken;
    textureFabric->resolvedPath = pxr::TfToken();
    *texCoordIndexFabric = static_cast<int>(texcoordIndex);
    *wrapSFabric = textureInfo.wrapS;
    *wrapTFabric = textureInfo.wrapT;
    *offsetFabric = UsdUtil::glmToUsdVector(glm::fvec2(offset));
    *rotationFabric = static_cast<float>(rotation);
    *scaleFabric = UsdUtil::glmToUsdVector(glm::fvec2(scale));
}

bool FabricMaterial::stageDestroyed() {
    // Add this guard to all public member functions, including constructors and destructors. Tile render resources can
    // continue to be processed asynchronously even after the tileset and USD stage have been destroyed, so prevent any
    // operations that would modify the stage.
    return _stageId != UsdUtil::getUsdStageId();
}

} // namespace cesium::omniverse
