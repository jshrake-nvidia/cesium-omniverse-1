#include "cesium/omniverse/FabricGeometryDefinition.h"

#include "cesium/omniverse/GltfUtil.h"

#ifdef CESIUM_OMNI_MSVC
#pragma push_macro("OPAQUE")
#undef OPAQUE
#endif

#include <CesiumGltf/Model.h>

namespace cesium::omniverse {

FabricGeometryDefinition::FabricGeometryDefinition(
    const CesiumGltf::Model& model,
    const CesiumGltf::MeshPrimitive& primitive,
    bool smoothNormals,
    bool hasImagery,
    bool disableMaterials) {

    const auto hasMaterial = GltfUtil::hasMaterial(primitive);
    const auto hasPrimitiveSt = GltfUtil::hasTexcoords(model, primitive, 0);
    const auto hasImagerySt = GltfUtil::hasImageryTexcoords(model, primitive, 0);

    const auto materialInfo = GltfUtil::getMaterialInfo(model, primitive);

    _hasMaterial = (hasMaterial || hasImagery) && !disableMaterials;
    _hasTexcoords = hasPrimitiveSt || hasImagerySt;
    _hasNormals = GltfUtil::hasNormals(model, primitive, smoothNormals);
    _hasVertexColors = GltfUtil::hasVertexColors(model, primitive, 0);
    _doubleSided = materialInfo.doubleSided;
}

bool FabricGeometryDefinition::hasMaterial() const {
    return _hasMaterial;
}

bool FabricGeometryDefinition::hasTexcoords() const {
    return _hasTexcoords;
}

bool FabricGeometryDefinition::hasNormals() const {
    return _hasNormals;
}

bool FabricGeometryDefinition::hasVertexColors() const {
    return _hasVertexColors;
}

bool FabricGeometryDefinition::getDoubleSided() const {
    return _doubleSided;
}

bool FabricGeometryDefinition::operator==(const FabricGeometryDefinition& other) const {
    if (_hasMaterial != other._hasMaterial) {
        return false;
    }

    if (_hasTexcoords != other._hasTexcoords) {
        return false;
    }

    if (_hasNormals != other._hasNormals) {
        return false;
    }

    if (_hasVertexColors != other._hasVertexColors) {
        return false;
    }

    if (_doubleSided != other._doubleSided) {
        return false;
    }

    return true;
}

} // namespace cesium::omniverse
