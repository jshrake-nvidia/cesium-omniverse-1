#pragma once

#include <carb/flatcache/StageWithHistory.h>
#include <pxr/base/tf/token.h>

// clang-format off

namespace cesium::omniverse::FabricTokens {
extern const carb::flatcache::TokenC alpha_cutoff;
extern const carb::flatcache::TokenC alpha_mode;
extern const carb::flatcache::TokenC base_alpha;
extern const carb::flatcache::TokenC base_color_factor;
extern const carb::flatcache::TokenC base_color_texture;
extern const carb::flatcache::TokenC baseColorTex;
extern const carb::flatcache::TokenC constant;
extern const carb::flatcache::TokenC displacement;
extern const carb::flatcache::TokenC doubleSided;
extern const carb::flatcache::TokenC emissive_factor;
extern const carb::flatcache::TokenC faceVertexCounts;
extern const carb::flatcache::TokenC faceVertexIndices;
extern const carb::flatcache::TokenC gltf_material;
extern const carb::flatcache::TokenC gltf_pbr_mdl;
extern const carb::flatcache::TokenC gltf_texture_lookup;
extern const carb::flatcache::TokenC info_id;
extern const carb::flatcache::TokenC info_sourceAsset_subIdentifier;
extern const carb::flatcache::TokenC Material;
extern const carb::flatcache::TokenC materialId;
extern const carb::flatcache::TokenC MaterialNetwork;
extern const carb::flatcache::TokenC Mesh;
extern const carb::flatcache::TokenC metallic_factor;
extern const carb::flatcache::TokenC none;
extern const carb::flatcache::TokenC offset;
extern const carb::flatcache::TokenC out;
extern const carb::flatcache::TokenC points;
extern const carb::flatcache::TokenC primvarInterpolations;
extern const carb::flatcache::TokenC primvars;
extern const carb::flatcache::TokenC primvars_displayColor;
extern const carb::flatcache::TokenC primvars_displayOpacity;
extern const carb::flatcache::TokenC primvars_normals;
extern const carb::flatcache::TokenC primvars_st;
extern const carb::flatcache::TokenC rotation;
extern const carb::flatcache::TokenC roughness_factor;
extern const carb::flatcache::TokenC scale;
extern const carb::flatcache::TokenC Shader;
extern const carb::flatcache::TokenC subdivisionScheme;
extern const carb::flatcache::TokenC surface;
extern const carb::flatcache::TokenC tex_coord_index;
extern const carb::flatcache::TokenC texture;
extern const carb::flatcache::TokenC vertex;
extern const carb::flatcache::TokenC wrap_s;
extern const carb::flatcache::TokenC wrap_t;
extern const carb::flatcache::TokenC _auto;
extern const carb::flatcache::TokenC _cesium_localToEcefTransform;
extern const carb::flatcache::TokenC _cesium_tileId;
extern const carb::flatcache::TokenC _cesium_tilesetId;
extern const carb::flatcache::TokenC _deletedPrims;
extern const carb::flatcache::TokenC _localExtent;
extern const carb::flatcache::TokenC _nodePaths;
extern const carb::flatcache::TokenC _paramColorSpace;
extern const carb::flatcache::TokenC _parameters;
extern const carb::flatcache::TokenC _relationships_inputId;
extern const carb::flatcache::TokenC _relationships_inputName;
extern const carb::flatcache::TokenC _relationships_outputId;
extern const carb::flatcache::TokenC _relationships_outputName;
extern const carb::flatcache::TokenC _terminals;
extern const carb::flatcache::TokenC _worldExtent;
extern const carb::flatcache::TokenC _worldOrientation;
extern const carb::flatcache::TokenC _worldPosition;
extern const carb::flatcache::TokenC _worldScale;
extern const carb::flatcache::TokenC _worldVisibility;
}

namespace cesium::omniverse::UsdTokens {
extern const pxr::TfToken& alpha_cutoff;
extern const pxr::TfToken& alpha_mode;
extern const pxr::TfToken& base_alpha;
extern const pxr::TfToken& base_color_factor;
extern const pxr::TfToken& base_color_texture;
extern const pxr::TfToken& baseColorTex;
extern const pxr::TfToken& constant;
extern const pxr::TfToken& displacement;
extern const pxr::TfToken& doubleSided;
extern const pxr::TfToken& emissive_factor;
extern const pxr::TfToken& faceVertexCounts;
extern const pxr::TfToken& faceVertexIndices;
extern const pxr::TfToken& gltf_material;
extern const pxr::TfToken& gltf_pbr_mdl;
extern const pxr::TfToken& gltf_texture_lookup;
extern const pxr::TfToken& info_id;
extern const pxr::TfToken& info_sourceAsset_subIdentifier;
extern const pxr::TfToken& Material;
extern const pxr::TfToken& materialId;
extern const pxr::TfToken& MaterialNetwork;
extern const pxr::TfToken& Mesh;
extern const pxr::TfToken& metallic_factor;
extern const pxr::TfToken& none;
extern const pxr::TfToken& offset;
extern const pxr::TfToken& out;
extern const pxr::TfToken& points;
extern const pxr::TfToken& primvarInterpolations;
extern const pxr::TfToken& primvars;
extern const pxr::TfToken& primvars_displayColor;
extern const pxr::TfToken& primvars_displayOpacity;
extern const pxr::TfToken& primvars_normals;
extern const pxr::TfToken& primvars_st;
extern const pxr::TfToken& rotation;
extern const pxr::TfToken& roughness_factor;
extern const pxr::TfToken& scale;
extern const pxr::TfToken& Shader;
extern const pxr::TfToken& subdivisionScheme;
extern const pxr::TfToken& surface;
extern const pxr::TfToken& tex_coord_index;
extern const pxr::TfToken& texture;
extern const pxr::TfToken& vertex;
extern const pxr::TfToken& wrap_s;
extern const pxr::TfToken& wrap_t;
extern const pxr::TfToken& _auto;
extern const pxr::TfToken& _cesium_localToEcefTransform;
extern const pxr::TfToken& _cesium_tileId;
extern const pxr::TfToken& _cesium_tilesetId;
extern const pxr::TfToken& _deletedPrims;
extern const pxr::TfToken& _localExtent;
extern const pxr::TfToken& _nodePaths;
extern const pxr::TfToken& _paramColorSpace;
extern const pxr::TfToken& _parameters;
extern const pxr::TfToken& _relationships_inputId;
extern const pxr::TfToken& _relationships_inputName;
extern const pxr::TfToken& _relationships_outputId;
extern const pxr::TfToken& _relationships_outputName;
extern const pxr::TfToken& _terminals;
extern const pxr::TfToken& _worldExtent;
extern const pxr::TfToken& _worldOrientation;
extern const pxr::TfToken& _worldPosition;
extern const pxr::TfToken& _worldScale;
extern const pxr::TfToken& _worldVisibility;
}

namespace cesium::omniverse::FabricTypes {
const carb::flatcache::Type alpha_cutoff(carb::flatcache::BaseDataType::eFloat, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type alpha_mode(carb::flatcache::BaseDataType::eInt, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type base_alpha(carb::flatcache::BaseDataType::eFloat, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type base_color_factor(carb::flatcache::BaseDataType::eFloat, 3, 0, carb::flatcache::AttributeRole::eColor);
const carb::flatcache::Type doubleSided(carb::flatcache::BaseDataType::eBool, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type emissive_factor(carb::flatcache::BaseDataType::eFloat, 3, 0, carb::flatcache::AttributeRole::eColor);
const carb::flatcache::Type faceVertexCounts(carb::flatcache::BaseDataType::eInt, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type faceVertexIndices(carb::flatcache::BaseDataType::eInt, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type info_id(carb::flatcache::BaseDataType::eToken, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type info_sourceAsset_subIdentifier(carb::flatcache::BaseDataType::eToken, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type Material(carb::flatcache::BaseDataType::eTag, 1, 0, carb::flatcache::AttributeRole::ePrimTypeName);
const carb::flatcache::Type materialId(carb::flatcache::BaseDataType::eUInt64, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type MaterialNetwork(carb::flatcache::BaseDataType::eTag, 1, 0, carb::flatcache::AttributeRole::ePrimTypeName);
const carb::flatcache::Type Mesh(carb::flatcache::BaseDataType::eTag, 1, 0, carb::flatcache::AttributeRole::ePrimTypeName);
const carb::flatcache::Type metallic_factor(carb::flatcache::BaseDataType::eFloat, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type offset(carb::flatcache::BaseDataType::eFloat, 2, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type points(carb::flatcache::BaseDataType::eFloat, 3, 1, carb::flatcache::AttributeRole::ePosition);
const carb::flatcache::Type primvarInterpolations(carb::flatcache::BaseDataType::eToken, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type primvars(carb::flatcache::BaseDataType::eToken, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type primvars_displayColor(carb::flatcache::BaseDataType::eFloat, 3, 1, carb::flatcache::AttributeRole::eColor);
const carb::flatcache::Type primvars_displayOpacity(carb::flatcache::BaseDataType::eFloat, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type primvars_normals(carb::flatcache::BaseDataType::eFloat, 3, 1, carb::flatcache::AttributeRole::eNormal);
const carb::flatcache::Type primvars_st(carb::flatcache::BaseDataType::eFloat, 2, 1, carb::flatcache::AttributeRole::eTexCoord);
const carb::flatcache::Type rotation(carb::flatcache::BaseDataType::eFloat, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type roughness_factor(carb::flatcache::BaseDataType::eFloat, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type scale(carb::flatcache::BaseDataType::eFloat, 2, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type Shader(carb::flatcache::BaseDataType::eTag, 1, 0, carb::flatcache::AttributeRole::ePrimTypeName);
const carb::flatcache::Type subdivisionScheme(carb::flatcache::BaseDataType::eToken, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type tex_coord_index(carb::flatcache::BaseDataType::eInt, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type texture(carb::flatcache::BaseDataType::eAsset, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type wrap_s(carb::flatcache::BaseDataType::eInt, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type wrap_t(carb::flatcache::BaseDataType::eInt, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _cesium_localToEcefTransform(carb::flatcache::BaseDataType::eDouble, 16, 0, carb::flatcache::AttributeRole::eMatrix);
const carb::flatcache::Type _cesium_tileId(carb::flatcache::BaseDataType::eInt64, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _cesium_tilesetId(carb::flatcache::BaseDataType::eInt64, 1, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _localExtent(carb::flatcache::BaseDataType::eDouble, 6, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _nodePaths(carb::flatcache::BaseDataType::eUInt64, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _paramColorSpace(carb::flatcache::BaseDataType::eToken, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _parameters(carb::flatcache::BaseDataType::eToken, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _relationships_inputId(carb::flatcache::BaseDataType::eUInt64, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _relationships_inputName(carb::flatcache::BaseDataType::eToken, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _relationships_outputId(carb::flatcache::BaseDataType::eUInt64, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _relationships_outputName(carb::flatcache::BaseDataType::eToken, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _terminals(carb::flatcache::BaseDataType::eUInt64, 1, 1, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _worldExtent(carb::flatcache::BaseDataType::eDouble, 6, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _worldOrientation(carb::flatcache::BaseDataType::eFloat, 4, 0, carb::flatcache::AttributeRole::eQuaternion);
const carb::flatcache::Type _worldPosition(carb::flatcache::BaseDataType::eDouble, 3, 0, carb::flatcache::AttributeRole::eNone);
const carb::flatcache::Type _worldScale(carb::flatcache::BaseDataType::eFloat, 3, 0, carb::flatcache::AttributeRole::eVector);
const carb::flatcache::Type _worldVisibility(carb::flatcache::BaseDataType::eBool, 1, 0, carb::flatcache::AttributeRole::eNone);
}
// clang-format on
