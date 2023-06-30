#pragma once

#include "cesium/omniverse/FabricGeometryDefinition.h"

#include <glm/glm.hpp>
#include <omni/fabric/IPath.h>
#include <pxr/usd/sdf/path.h>

namespace CesiumGltf {
struct MeshPrimitive;
struct Model;
} // namespace CesiumGltf

namespace cesium::omniverse {

class FabricMaterial;

class FabricGeometry {
  public:
    FabricGeometry(
        const pxr::SdfPath& path,
        const FabricGeometryDefinition& geometryDefinition,
        bool debugRandomColors);
    ~FabricGeometry();

    void setTile(
        int64_t tilesetId,
        int64_t tileId,
        const glm::dmat4& ecefToUsdTransform,
        const glm::dmat4& gltfToEcefTransform,
        const glm::dmat4& nodeTransform,
        const CesiumGltf::Model& model,
        const CesiumGltf::MeshPrimitive& primitive,
        bool smoothNormals,
        bool hasImagery,
        uint64_t imageryTexcoordSetIndex);

    void setActive(bool active);
    void setVisibility(bool visible);

    [[nodiscard]] omni::fabric::Path getPathFabric() const;
    [[nodiscard]] const FabricGeometryDefinition& getGeometryDefinition() const;

    void assignMaterial(const std::shared_ptr<FabricMaterial>& material);

  private:
    void initialize();
    void reset();

    const omni::fabric::Path _pathFabric;
    const FabricGeometryDefinition _geometryDefinition;
    const bool _debugRandomColors;
};

} // namespace cesium::omniverse
