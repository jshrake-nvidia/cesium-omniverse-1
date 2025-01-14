#include "cesium/omniverse/UsdUtil.h"

#include "CesiumUsdSchemas/webMapServiceRasterOverlay.h"

#include "cesium/omniverse/AssetRegistry.h"
#include "cesium/omniverse/Context.h"
#include "cesium/omniverse/CppUtil.h"
#include "cesium/omniverse/MathUtil.h"
#include "cesium/omniverse/OmniData.h"
#include "cesium/omniverse/OmniGeoreference.h"
#include "cesium/omniverse/UsdScopedEdit.h"
#include "cesium/omniverse/UsdTokens.h"
#include "cesium/omniverse/Viewport.h"

#include <Cesium3DTilesSelection/ViewState.h>
#include <CesiumGeometry/Transforms.h>
#include <CesiumGeospatial/Cartographic.h>
#include <CesiumGeospatial/Ellipsoid.h>
#include <CesiumGeospatial/GlobeAnchor.h>
#include <CesiumGeospatial/GlobeTransforms.h>
#include <CesiumGeospatial/LocalHorizontalCoordinateSystem.h>
#include <CesiumUsdSchemas/data.h>
#include <CesiumUsdSchemas/georeference.h>
#include <CesiumUsdSchemas/globeAnchorAPI.h>
#include <CesiumUsdSchemas/ionRasterOverlay.h>
#include <CesiumUsdSchemas/ionServer.h>
#include <CesiumUsdSchemas/polygonRasterOverlay.h>
#include <CesiumUsdSchemas/session.h>
#include <CesiumUsdSchemas/tileMapServiceRasterOverlay.h>
#include <CesiumUsdSchemas/tileset.h>
#include <CesiumUsdSchemas/webMapServiceRasterOverlay.h>
#include <CesiumUsdSchemas/webMapTileServiceRasterOverlay.h>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <omni/ui/ImageProvider/DynamicTextureProvider.h>
#include <pxr/base/gf/rotation.h>
#include <pxr/usd/sdf/primSpec.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/timeCode.h>
#include <pxr/usd/usdGeom/metrics.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <pxr/usd/usdShade/material.h>
#include <pxr/usd/usdShade/shader.h>
#include <spdlog/fmt/fmt.h>

#include <cctype>

namespace cesium::omniverse::UsdUtil {

namespace {

bool getDebugDisableGeoreferencing(const Context& context) {
    const auto pData = context.getAssetRegistry().getFirstData();
    if (!pData) {
        return false;
    }

    return pData->getDebugDisableGeoreferencing();
}

} // namespace

glm::dvec3 usdToGlmVector(const pxr::GfVec3d& vector) {
    return {vector[0], vector[1], vector[2]};
}

glm::fvec3 usdToGlmVector(const pxr::GfVec3f& vector) {
    return {vector[0], vector[1], vector[2]};
}

glm::dmat4 usdToGlmMatrix(const pxr::GfMatrix4d& matrix) {
    // USD is row-major with left-to-right matrix multiplication
    // glm is column-major with right-to-left matrix multiplication
    // This means they have the same data layout
    return {
        matrix[0][0],
        matrix[0][1],
        matrix[0][2],
        matrix[0][3],
        matrix[1][0],
        matrix[1][1],
        matrix[1][2],
        matrix[1][3],
        matrix[2][0],
        matrix[2][1],
        matrix[2][2],
        matrix[2][3],
        matrix[3][0],
        matrix[3][1],
        matrix[3][2],
        matrix[3][3],
    };
}

glm::dquat usdToGlmQuat(const pxr::GfQuatd& quat) {
    const auto real = quat.GetReal();
    const auto imaginary = usdToGlmVector(quat.GetImaginary());
    return {real, imaginary.x, imaginary.y, imaginary.z};
}

glm::fquat usdToGlmQuat(const pxr::GfQuatf& quat) {
    const auto real = quat.GetReal();
    const auto imaginary = usdToGlmVector(quat.GetImaginary());
    return {real, imaginary.x, imaginary.y, imaginary.z};
}

std::array<glm::dvec3, 2> usdToGlmExtent(const pxr::GfRange3d& extent) {
    return {{usdToGlmVector(extent.GetMin()), usdToGlmVector(extent.GetMax())}};
}

pxr::GfVec3d glmToUsdVector(const glm::dvec3& vector) {
    return {vector.x, vector.y, vector.z};
}

pxr::GfVec2f glmToUsdVector(const glm::fvec2& vector) {
    return {vector.x, vector.y};
}

pxr::GfVec3f glmToUsdVector(const glm::fvec3& vector) {
    return {vector.x, vector.y, vector.z};
}

pxr::GfVec4f glmToUsdVector(const glm::fvec4& vector) {
    return {vector.x, vector.y, vector.z, vector.w};
}

pxr::GfRange3d glmToUsdExtent(const std::array<glm::dvec3, 2>& extent) {
    return {glmToUsdVector(extent[0]), glmToUsdVector(extent[1])};
}

pxr::GfQuatd glmToUsdQuat(const glm::dquat& quat) {
    return {quat.w, quat.x, quat.y, quat.z};
}

pxr::GfQuatf glmToUsdQuat(const glm::fquat& quat) {
    return {quat.w, quat.x, quat.y, quat.z};
}

pxr::GfMatrix4d glmToUsdMatrix(const glm::dmat4& matrix) {
    // USD is row-major with left-to-right matrix multiplication
    // glm is column-major with right-to-left matrix multiplication
    // This means they have the same data layout
    return pxr::GfMatrix4d{
        matrix[0][0],
        matrix[0][1],
        matrix[0][2],
        matrix[0][3],
        matrix[1][0],
        matrix[1][1],
        matrix[1][2],
        matrix[1][3],
        matrix[2][0],
        matrix[2][1],
        matrix[2][2],
        matrix[2][3],
        matrix[3][0],
        matrix[3][1],
        matrix[3][2],
        matrix[3][3],
    };
}

glm::dmat4 computePrimLocalToWorldTransform(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    const auto xform = pxr::UsdGeomXformable(prim);

    if (!isSchemaValid(xform)) {
        return glm::dmat4(1.0);
    }

    const auto time = pxr::UsdTimeCode::Default();
    const auto transform = xform.ComputeLocalToWorldTransform(time);
    return usdToGlmMatrix(transform);
}

glm::dmat4 computePrimWorldToLocalTransform(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return glm::affineInverse(computePrimLocalToWorldTransform(pStage, path));
}

glm::dmat4 computeEcefToStageTransform(const Context& context, const pxr::SdfPath& georeferencePath) {
    const auto disableGeoreferencing = getDebugDisableGeoreferencing(context);
    const auto pGeoreference =
        georeferencePath.IsEmpty() ? nullptr : context.getAssetRegistry().getGeoreference(georeferencePath);

    if (disableGeoreferencing || !pGeoreference) {
        const auto zUp = getUsdUpAxis(context.getUsdStage()) == pxr::UsdGeomTokens->z;
        const auto axisConversion = zUp ? glm::dmat4(1.0) : CesiumGeometry::Transforms::Z_UP_TO_Y_UP;
        const auto scale = glm::scale(glm::dmat4(1.0), glm::dvec3(1.0 / getUsdMetersPerUnit(context.getUsdStage())));
        return scale * axisConversion;
    }

    return pGeoreference->getLocalCoordinateSystem().getEcefToLocalTransformation();
}

glm::dmat4 computeEcefToPrimWorldTransform(
    const Context& context,
    const pxr::SdfPath& georeferencePath,
    const pxr::SdfPath& primPath) {
    const auto ecefToStageTransform = computeEcefToStageTransform(context, georeferencePath);
    const auto primLocalToWorldTransform = computePrimLocalToWorldTransform(context.getUsdStage(), primPath);
    return primLocalToWorldTransform * ecefToStageTransform;
}

glm::dmat4 computePrimWorldToEcefTransform(
    const Context& context,
    const pxr::SdfPath& georeferencePath,
    const pxr::SdfPath& primPath) {
    return glm::affineInverse(computeEcefToPrimWorldTransform(context, georeferencePath, primPath));
}

glm::dmat4 computeEcefToPrimLocalTransform(
    const Context& context,
    const pxr::SdfPath& georeferencePath,
    const pxr::SdfPath& primPath) {
    const auto ecefToStageTransform = computeEcefToStageTransform(context, georeferencePath);
    const auto primWorldToLocalTransform = computePrimWorldToLocalTransform(context.getUsdStage(), primPath);
    return primWorldToLocalTransform * ecefToStageTransform;
}

glm::dmat4 computePrimLocalToEcefTransform(
    const Context& context,
    const pxr::SdfPath& georeferencePath,
    const pxr::SdfPath& primPath) {
    return glm::affineInverse(computeEcefToPrimLocalTransform(context, georeferencePath, primPath));
}

Cesium3DTilesSelection::ViewState computeViewState(
    const Context& context,
    const pxr::SdfPath& georeferencePath,
    const pxr::SdfPath& primPath,
    const Viewport& viewport) {
    const auto& viewMatrix = viewport.viewMatrix;
    const auto& projMatrix = viewport.projMatrix;
    const auto width = viewport.width;
    const auto height = viewport.height;

    const auto primWorldToEcefTransform = computePrimWorldToEcefTransform(context, georeferencePath, primPath);
    const auto inverseView = glm::affineInverse(viewMatrix);
    const auto usdCameraUp = glm::dvec3(inverseView[1]);
    const auto usdCameraFwd = glm::dvec3(-inverseView[2]);
    const auto usdCameraPosition = glm::dvec3(inverseView[3]);
    const auto cameraUp = glm::normalize(glm::dvec3(primWorldToEcefTransform * glm::dvec4(usdCameraUp, 0.0)));
    const auto cameraFwd = glm::normalize(glm::dvec3(primWorldToEcefTransform * glm::dvec4(usdCameraFwd, 0.0)));
    const auto cameraPosition = glm::dvec3(primWorldToEcefTransform * glm::dvec4(usdCameraPosition, 1.0));

    const auto aspect = width / height;
    const auto verticalFov = 2.0 * glm::atan(1.0 / projMatrix[1][1]);
    const auto horizontalFov = 2.0 * glm::atan(glm::tan(verticalFov * 0.5) * aspect);

    return Cesium3DTilesSelection::ViewState::create(
        cameraPosition, cameraFwd, cameraUp, glm::dvec2(width, height), horizontalFov, verticalFov);
}

bool primExists(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pStage->GetPrimAtPath(path).IsValid();
}

bool isSchemaValid(const pxr::UsdSchemaBase& schema) {
    return schema.GetPrim().IsValid() && schema.GetSchemaKind() != pxr::UsdSchemaKind::Invalid;
}

bool isPrimVisible(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    // This is similar to isPrimVisible in kit-sdk/dev/include/omni/usd/UsdUtils.h
    const auto prim = pStage->GetPrimAtPath(path);
    const auto imageable = pxr::UsdGeomImageable(prim);

    if (!isSchemaValid(imageable)) {
        return false;
    }

    const auto time = pxr::UsdTimeCode::Default();
    const auto visibility = imageable.ComputeVisibility(time);
    return visibility != pxr::UsdGeomTokens->invisible;
}

const std::string& getName(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pStage->GetPrimAtPath(path).GetName().GetString();
}

pxr::TfToken getUsdUpAxis(const pxr::UsdStageWeakPtr& pStage) {
    return pxr::UsdGeomGetStageUpAxis(pStage);
}

double getUsdMetersPerUnit(const pxr::UsdStageWeakPtr& pStage) {
    return pxr::UsdGeomGetStageMetersPerUnit(pStage);
}

pxr::SdfPath getRootPath(const pxr::UsdStageWeakPtr& pStage) {
    return pStage->GetPseudoRoot().GetPath();
}

pxr::SdfPath
makeUniquePath(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& parentPath, const std::string& name) {
    pxr::UsdPrim prim;
    pxr::SdfPath path;
    auto copy = 0;

    do {
        const auto copyName = copy > 0 ? fmt::format("{}_{}", name, copy) : name;
        path = parentPath.AppendChild(pxr::TfToken(copyName));
        prim = pStage->GetPrimAtPath(path);
        ++copy;
    } while (prim.IsValid());

    return path;
}

std::string getSafeName(const std::string& name) {
    auto safeName = name;

    for (auto& c : safeName) {
        if (!std::isalnum(c)) {
            c = '_';
        }
    }

    return safeName;
}

pxr::TfToken getDynamicTextureProviderAssetPathToken(const std::string_view& name) {
    return pxr::TfToken(pxr::SdfAssetPath(fmt::format("dynamic://{}", name)).GetAssetPath());
}

pxr::CesiumData defineCesiumData(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumData::Define(pStage, path);
}

pxr::CesiumTileset defineCesiumTileset(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumTileset::Define(pStage, path);
}

pxr::CesiumIonRasterOverlay defineCesiumIonRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumIonRasterOverlay::Define(pStage, path);
}

pxr::CesiumPolygonRasterOverlay
defineCesiumPolygonRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumPolygonRasterOverlay::Define(pStage, path);
}

pxr::CesiumGeoreference defineCesiumGeoreference(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumGeoreference::Define(pStage, path);
}

pxr::CesiumIonServer defineCesiumIonServer(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumIonServer::Define(pStage, path);
}

pxr::CesiumGlobeAnchorAPI applyCesiumGlobeAnchor(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    assert(prim.IsValid() && prim.IsA<pxr::UsdGeomXformable>());
    return pxr::CesiumGlobeAnchorAPI::Apply(prim);
}

pxr::CesiumSession defineCesiumSession(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumSession::Define(pStage, path);
}

pxr::CesiumData getCesiumData(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumData::Get(pStage, path);
}

pxr::CesiumTileset getCesiumTileset(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumTileset::Get(pStage, path);
}

pxr::CesiumRasterOverlay getCesiumRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumRasterOverlay::Get(pStage, path);
}

pxr::CesiumIonRasterOverlay getCesiumIonRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumIonRasterOverlay::Get(pStage, path);
}

pxr::CesiumPolygonRasterOverlay
getCesiumPolygonRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumPolygonRasterOverlay::Get(pStage, path);
}

pxr::CesiumWebMapServiceRasterOverlay
getCesiumWebMapServiceRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumWebMapServiceRasterOverlay::Get(pStage, path);
}

pxr::CesiumTileMapServiceRasterOverlay
getCesiumTileMapServiceRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumTileMapServiceRasterOverlay::Get(pStage, path);
}

pxr::CesiumWebMapTileServiceRasterOverlay
getCesiumWebMapTileServiceRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumWebMapTileServiceRasterOverlay::Get(pStage, path);
}

pxr::CesiumGeoreference getCesiumGeoreference(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumGeoreference::Get(pStage, path);
}

pxr::CesiumGlobeAnchorAPI getCesiumGlobeAnchor(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumGlobeAnchorAPI::Get(pStage, path);
}

pxr::CesiumIonServer getCesiumIonServer(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::CesiumIonServer::Get(pStage, path);
}

// This is currently a pass-through to getUsdBasisCurves until
// issue with crashes in prims that inherit from BasisCurves is resolved
pxr::UsdGeomBasisCurves getCesiumCartographicPolygon(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return getUsdBasisCurves(pStage, path);
}

pxr::UsdShadeShader getUsdShader(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::UsdShadeShader::Get(pStage, path);
}

pxr::UsdGeomBasisCurves getUsdBasisCurves(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    return pxr::UsdGeomBasisCurves::Get(pStage, path);
}

pxr::CesiumSession getOrCreateCesiumSession(const pxr::UsdStageWeakPtr& pStage) {
    static const auto CesiumSessionPath = pxr::SdfPath("/CesiumSession");

    if (isCesiumSession(pStage, CesiumSessionPath)) {
        return pxr::CesiumSession::Get(pStage, CesiumSessionPath);
    }

    // Ensures that CesiumSession is created in the session layer
    const UsdScopedEdit scopedEdit(pStage);

    // Create the CesiumSession
    const auto cesiumSession = defineCesiumSession(pStage, CesiumSessionPath);

    // Prevent CesiumSession from being traversed and composed into the stage
    cesiumSession.GetPrim().SetActive(false);

    return cesiumSession;
}

bool isCesiumData(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::CesiumData>();
}

bool isCesiumTileset(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::CesiumTileset>();
}

bool isCesiumRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::CesiumRasterOverlay>();
}

bool isCesiumIonRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::CesiumIonRasterOverlay>();
}

bool isCesiumPolygonRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::CesiumPolygonRasterOverlay>();
}

bool isCesiumWebMapServiceRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::CesiumWebMapServiceRasterOverlay>();
}

bool isCesiumTileMapServiceRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::CesiumTileMapServiceRasterOverlay>();
}

bool isCesiumWebMapTileServiceRasterOverlay(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::CesiumWebMapTileServiceRasterOverlay>();
}

bool isCesiumGeoreference(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::CesiumGeoreference>();
}

bool isCesiumIonServer(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::CesiumIonServer>();
}

bool isCesiumCartographicPolygon(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }
    if (!prim.IsA<pxr::UsdGeomBasisCurves>()) {
        return false;
    }
    return prim.HasAPI<pxr::CesiumGlobeAnchorAPI>();
}

bool isCesiumSession(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::CesiumSession>();
}

bool hasCesiumGlobeAnchor(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::UsdGeomXformable>() && prim.HasAPI<pxr::CesiumGlobeAnchorAPI>();
}

bool isUsdShader(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::UsdShadeShader>();
}

bool isUsdMaterial(const pxr::UsdStageWeakPtr& pStage, const pxr::SdfPath& path) {
    const auto prim = pStage->GetPrimAtPath(path);
    if (!prim.IsValid()) {
        return false;
    }

    return prim.IsA<pxr::UsdShadeMaterial>();
}

glm::dvec3 getTranslate(const pxr::UsdGeomXformOp& translateOp) {
    if (translateOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionDouble) {
        pxr::GfVec3d translation;
        translateOp.Get(&translation);
        return UsdUtil::usdToGlmVector(translation);
    } else if (translateOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionFloat) {
        pxr::GfVec3f translation;
        translateOp.Get(&translation);
        return glm::dvec3(UsdUtil::usdToGlmVector(translation));
    }

    return glm::dvec3(0.0);
}

glm::dvec3 getRotate(const pxr::UsdGeomXformOp& rotateOp) {
    if (rotateOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionDouble) {
        pxr::GfVec3d rotation;
        rotateOp.Get(&rotation);
        return UsdUtil::usdToGlmVector(rotation);
    } else if (rotateOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionFloat) {
        pxr::GfVec3f rotation;
        rotateOp.Get(&rotation);
        return glm::dvec3(UsdUtil::usdToGlmVector(rotation));
    }

    return glm::dvec3(0.0);
}

glm::dquat getOrient(const pxr::UsdGeomXformOp& orientOp) {
    if (orientOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionDouble) {
        pxr::GfQuatd orient;
        orientOp.Get(&orient);
        return UsdUtil::usdToGlmQuat(orient);
    } else if (orientOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionFloat) {
        pxr::GfQuatf orient;
        orientOp.Get(&orient);
        return glm::dquat(UsdUtil::usdToGlmQuat(orient));
    }

    return {1.0, 0.0, 0.0, 0.0};
}

glm::dvec3 getScale(const pxr::UsdGeomXformOp& scaleOp) {
    if (scaleOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionDouble) {
        pxr::GfVec3d scale;
        scaleOp.Get(&scale);
        return UsdUtil::usdToGlmVector(scale);
    } else if (scaleOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionFloat) {
        pxr::GfVec3f scale;
        scaleOp.Get(&scale);
        return glm::dvec3(UsdUtil::usdToGlmVector(scale));
    }

    return glm::dvec3(1.0);
}

void setTranslate(pxr::UsdGeomXformOp& translateOp, const glm::dvec3& translate) {
    if (translateOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionDouble) {
        translateOp.Set(UsdUtil::glmToUsdVector(translate));
    } else if (translateOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionFloat) {
        translateOp.Set(UsdUtil::glmToUsdVector(glm::fvec3(translate)));
    }
}

void setRotate(pxr::UsdGeomXformOp& rotateOp, const glm::dvec3& rotate) {
    if (rotateOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionDouble) {
        rotateOp.Set(UsdUtil::glmToUsdVector(rotate));
    } else if (rotateOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionFloat) {
        rotateOp.Set(UsdUtil::glmToUsdVector(glm::fvec3(rotate)));
    }
}

void setOrient(pxr::UsdGeomXformOp& orientOp, const glm::dquat& orient) {
    if (orientOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionDouble) {
        orientOp.Set(UsdUtil::glmToUsdQuat(orient));
    } else if (orientOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionFloat) {
        orientOp.Set(UsdUtil::glmToUsdQuat(glm::fquat(orient)));
    }
}

void setScale(pxr::UsdGeomXformOp& scaleOp, const glm::dvec3& scale) {
    if (scaleOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionDouble) {
        scaleOp.Set(UsdUtil::glmToUsdVector(scale));
    } else if (scaleOp.GetPrecision() == pxr::UsdGeomXformOp::PrecisionFloat) {
        scaleOp.Set(UsdUtil::glmToUsdVector(glm::fvec3(scale)));
    }
}

std::optional<TranslateRotateScaleOps> getOrCreateTranslateRotateScaleOps(const pxr::UsdGeomXformable& xformable) {
    pxr::UsdGeomXformOp translateOp;
    pxr::UsdGeomXformOp rotateOp;
    pxr::UsdGeomXformOp orientOp;
    pxr::UsdGeomXformOp scaleOp;

    int64_t translateOpIndex = -1;
    int64_t rotateOpIndex = -1;
    int64_t orientOpIndex = -1;
    int64_t scaleOpIndex = -1;

    int64_t opCount = 0;

    bool resetsXformStack;
    const auto xformOps = xformable.GetOrderedXformOps(&resetsXformStack);

    auto eulerAngleOrder = MathUtil::EulerAngleOrder::XYZ;

    for (const auto& xformOp : xformOps) {
        switch (xformOp.GetOpType()) {
            case pxr::UsdGeomXformOp::TypeTranslate:
                if (translateOpIndex == -1) {
                    translateOp = xformOp;
                    translateOpIndex = opCount;
                }
                break;
            case pxr::UsdGeomXformOp::TypeRotateXYZ:
                if (rotateOpIndex == -1) {
                    eulerAngleOrder = MathUtil::EulerAngleOrder::XYZ;
                    rotateOp = xformOp;
                    rotateOpIndex = opCount;
                }
                break;
            case pxr::UsdGeomXformOp::TypeRotateXZY:
                if (rotateOpIndex == -1) {
                    eulerAngleOrder = MathUtil::EulerAngleOrder::XZY;
                    rotateOp = xformOp;
                    rotateOpIndex = opCount;
                }
                break;
            case pxr::UsdGeomXformOp::TypeRotateYXZ:
                if (rotateOpIndex == -1) {
                    eulerAngleOrder = MathUtil::EulerAngleOrder::YXZ;
                    rotateOp = xformOp;
                    rotateOpIndex = opCount;
                }
                break;
            case pxr::UsdGeomXformOp::TypeRotateYZX:
                if (rotateOpIndex == -1) {
                    eulerAngleOrder = MathUtil::EulerAngleOrder::YZX;
                    rotateOp = xformOp;
                    rotateOpIndex = opCount;
                }
                break;
            case pxr::UsdGeomXformOp::TypeRotateZXY:
                if (rotateOpIndex == -1) {
                    eulerAngleOrder = MathUtil::EulerAngleOrder::ZXY;
                    rotateOp = xformOp;
                    rotateOpIndex = opCount;
                }
                break;
            case pxr::UsdGeomXformOp::TypeRotateZYX:
                if (rotateOpIndex == -1) {
                    eulerAngleOrder = MathUtil::EulerAngleOrder::ZYX;
                    rotateOp = xformOp;
                    rotateOpIndex = opCount;
                }
                break;
            case pxr::UsdGeomXformOp::TypeOrient:
                if (orientOpIndex == -1) {
                    orientOp = xformOp;
                    orientOpIndex = opCount;
                }
                break;
            case pxr::UsdGeomXformOp::TypeScale:
                if (scaleOpIndex == -1) {
                    scaleOp = xformOp;
                    scaleOpIndex = opCount;
                }
                break;
            default:
                break;
        }

        ++opCount;
    }

    const auto translateOpDefined = translateOp.IsDefined();
    const auto rotateOpDefined = rotateOp.IsDefined();
    const auto orientOpDefined = orientOp.IsDefined();
    const auto scaleOpDefined = scaleOp.IsDefined();

    if (rotateOpDefined && orientOpDefined) {
        return std::nullopt;
    }

    opCount = 0;

    if (translateOpDefined && translateOpIndex != opCount++) {
        return std::nullopt;
    }

    if (rotateOpDefined && rotateOpIndex != opCount++) {
        return std::nullopt;
    }

    if (orientOpDefined && orientOpIndex != opCount++) {
        return std::nullopt;
    }

    if (scaleOpDefined && scaleOpIndex != opCount++) {
        return std::nullopt;
    }

    const auto isPrecisionSupported = [](pxr::UsdGeomXformOp::Precision precision) {
        return precision == pxr::UsdGeomXformOp::PrecisionDouble || precision == pxr::UsdGeomXformOp::PrecisionFloat;
    };

    if (translateOpDefined && !isPrecisionSupported(translateOp.GetPrecision())) {
        return std::nullopt;
    }

    if (rotateOpDefined && !isPrecisionSupported(rotateOp.GetPrecision())) {
        return std::nullopt;
    }

    if (orientOpDefined && !isPrecisionSupported(orientOp.GetPrecision())) {
        return std::nullopt;
    }

    if (scaleOpDefined && !isPrecisionSupported(scaleOp.GetPrecision())) {
        return std::nullopt;
    }

    if (!translateOpDefined) {
        translateOp = xformable.AddTranslateOp(pxr::UsdGeomXformOp::PrecisionDouble);
        translateOp.Set(UsdUtil::glmToUsdVector(glm::dvec3(0.0)));
    }

    if (!rotateOpDefined && !orientOpDefined) {
        rotateOp = xformable.AddRotateXYZOp(pxr::UsdGeomXformOp::PrecisionDouble);
        rotateOp.Set(UsdUtil::glmToUsdVector(glm::dvec3(0.0)));
    }

    if (!scaleOpDefined) {
        scaleOp = xformable.AddScaleOp(pxr::UsdGeomXformOp::PrecisionDouble);
        scaleOp.Set(UsdUtil::glmToUsdVector(glm::dvec3(1.0)));
    }

    if (!translateOpDefined || (!rotateOpDefined && !orientOpDefined) || !scaleOpDefined) {
        std::vector<pxr::UsdGeomXformOp> reorderedXformOps;

        if (orientOpDefined) {
            reorderedXformOps = {translateOp, orientOp, scaleOp};
        } else {
            reorderedXformOps = {translateOp, rotateOp, scaleOp};
        }

        // Add back additional xform ops like xformOp:rotateX:unitsResolve
        reorderedXformOps.insert(reorderedXformOps.end(), xformOps.begin() + opCount, xformOps.end());
        xformable.SetXformOpOrder(reorderedXformOps);
    }

    if (orientOpDefined) {
        return TranslateRotateScaleOps{translateOp, orientOp, scaleOp, eulerAngleOrder};
    }

    return TranslateRotateScaleOps{translateOp, rotateOp, scaleOp, eulerAngleOrder};
}

} // namespace cesium::omniverse::UsdUtil
