#include ".//tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

CesiumTokensType::CesiumTokensType() :
    cesiumAlpha("cesium:alpha", TfToken::Immortal),
    cesiumAnchorAdjustOrientationForGlobeWhenMoving("cesium:anchor:adjustOrientationForGlobeWhenMoving", TfToken::Immortal),
    cesiumAnchorDetectTransformChanges("cesium:anchor:detectTransformChanges", TfToken::Immortal),
    cesiumAnchorGeoreferenceBinding("cesium:anchor:georeferenceBinding", TfToken::Immortal),
    cesiumAnchorHeight("cesium:anchor:height", TfToken::Immortal),
    cesiumAnchorLatitude("cesium:anchor:latitude", TfToken::Immortal),
    cesiumAnchorLongitude("cesium:anchor:longitude", TfToken::Immortal),
    cesiumAnchorPosition("cesium:anchor:position", TfToken::Immortal),
    cesiumBaseUrl("cesium:baseUrl", TfToken::Immortal),
    cesiumCartographicPolygonBinding("cesium:cartographicPolygonBinding", TfToken::Immortal),
    cesiumCulledScreenSpaceError("cesium:culledScreenSpaceError", TfToken::Immortal),
    cesiumDebugDisableGeometryPool("cesium:debug:disableGeometryPool", TfToken::Immortal),
    cesiumDebugDisableGeoreferencing("cesium:debug:disableGeoreferencing", TfToken::Immortal),
    cesiumDebugDisableMaterialPool("cesium:debug:disableMaterialPool", TfToken::Immortal),
    cesiumDebugDisableMaterials("cesium:debug:disableMaterials", TfToken::Immortal),
    cesiumDebugDisableTexturePool("cesium:debug:disableTexturePool", TfToken::Immortal),
    cesiumDebugDisableTextures("cesium:debug:disableTextures", TfToken::Immortal),
    cesiumDebugGeometryPoolInitialCapacity("cesium:debug:geometryPoolInitialCapacity", TfToken::Immortal),
    cesiumDebugMaterialPoolInitialCapacity("cesium:debug:materialPoolInitialCapacity", TfToken::Immortal),
    cesiumDebugRandomColors("cesium:debug:randomColors", TfToken::Immortal),
    cesiumDebugTexturePoolInitialCapacity("cesium:debug:texturePoolInitialCapacity", TfToken::Immortal),
    cesiumDisplayName("cesium:displayName", TfToken::Immortal),
    cesiumEcefToUsdTransform("cesium:ecefToUsdTransform", TfToken::Immortal),
    cesiumEnableFogCulling("cesium:enableFogCulling", TfToken::Immortal),
    cesiumEnableFrustumCulling("cesium:enableFrustumCulling", TfToken::Immortal),
    cesiumEnforceCulledScreenSpaceError("cesium:enforceCulledScreenSpaceError", TfToken::Immortal),
    cesiumExcludeSelectedTiles("cesium:excludeSelectedTiles", TfToken::Immortal),
    cesiumForbidHoles("cesium:forbidHoles", TfToken::Immortal),
    cesiumGeoreferenceBinding("cesium:georeferenceBinding", TfToken::Immortal),
    cesiumGeoreferenceOriginHeight("cesium:georeferenceOrigin:height", TfToken::Immortal),
    cesiumGeoreferenceOriginLatitude("cesium:georeferenceOrigin:latitude", TfToken::Immortal),
    cesiumGeoreferenceOriginLongitude("cesium:georeferenceOrigin:longitude", TfToken::Immortal),
    cesiumInvertSelection("cesium:invertSelection", TfToken::Immortal),
    cesiumIonAccessToken("cesium:ionAccessToken", TfToken::Immortal),
    cesiumIonAssetId("cesium:ionAssetId", TfToken::Immortal),
    cesiumIonServerApiUrl("cesium:ionServerApiUrl", TfToken::Immortal),
    cesiumIonServerApplicationId("cesium:ionServerApplicationId", TfToken::Immortal),
    cesiumIonServerBinding("cesium:ionServerBinding", TfToken::Immortal),
    cesiumIonServerUrl("cesium:ionServerUrl", TfToken::Immortal),
    cesiumLayers("cesium:layers", TfToken::Immortal),
    cesiumLoadingDescendantLimit("cesium:loadingDescendantLimit", TfToken::Immortal),
    cesiumMainThreadLoadingTimeLimit("cesium:mainThreadLoadingTimeLimit", TfToken::Immortal),
    cesiumMaximumCachedBytes("cesium:maximumCachedBytes", TfToken::Immortal),
    cesiumMaximumLevel("cesium:maximumLevel", TfToken::Immortal),
    cesiumMaximumScreenSpaceError("cesium:maximumScreenSpaceError", TfToken::Immortal),
    cesiumMaximumSimultaneousTileLoads("cesium:maximumSimultaneousTileLoads", TfToken::Immortal),
    cesiumMaximumTextureSize("cesium:maximumTextureSize", TfToken::Immortal),
    cesiumMinimumLevel("cesium:minimumLevel", TfToken::Immortal),
    cesiumOverlayRenderMethod("cesium:overlayRenderMethod", TfToken::Immortal),
    cesiumPreloadAncestors("cesium:preloadAncestors", TfToken::Immortal),
    cesiumPreloadSiblings("cesium:preloadSiblings", TfToken::Immortal),
    cesiumProjectDefaultIonAccessToken("cesium:projectDefaultIonAccessToken", TfToken::Immortal),
    cesiumProjectDefaultIonAccessTokenId("cesium:projectDefaultIonAccessTokenId", TfToken::Immortal),
    cesiumRasterOverlayBinding("cesium:rasterOverlayBinding", TfToken::Immortal),
    cesiumSelectedIonServer("cesium:selectedIonServer", TfToken::Immortal),
    cesiumShowCreditsOnScreen("cesium:showCreditsOnScreen", TfToken::Immortal),
    cesiumSmoothNormals("cesium:smoothNormals", TfToken::Immortal),
    cesiumSourceType("cesium:sourceType", TfToken::Immortal),
    cesiumSubTileCacheBytes("cesium:subTileCacheBytes", TfToken::Immortal),
    cesiumSuspendUpdate("cesium:suspendUpdate", TfToken::Immortal),
    cesiumTileHeight("cesium:tileHeight", TfToken::Immortal),
    cesiumTileWidth("cesium:tileWidth", TfToken::Immortal),
    cesiumUrl("cesium:url", TfToken::Immortal),
    clip("clip", TfToken::Immortal),
    ion("ion", TfToken::Immortal),
    overlay("overlay", TfToken::Immortal),
    url("url", TfToken::Immortal),
    allTokens({
        cesiumAlpha,
        cesiumAnchorAdjustOrientationForGlobeWhenMoving,
        cesiumAnchorDetectTransformChanges,
        cesiumAnchorGeoreferenceBinding,
        cesiumAnchorHeight,
        cesiumAnchorLatitude,
        cesiumAnchorLongitude,
        cesiumAnchorPosition,
        cesiumBaseUrl,
        cesiumCartographicPolygonBinding,
        cesiumCulledScreenSpaceError,
        cesiumDebugDisableGeometryPool,
        cesiumDebugDisableGeoreferencing,
        cesiumDebugDisableMaterialPool,
        cesiumDebugDisableMaterials,
        cesiumDebugDisableTexturePool,
        cesiumDebugDisableTextures,
        cesiumDebugGeometryPoolInitialCapacity,
        cesiumDebugMaterialPoolInitialCapacity,
        cesiumDebugRandomColors,
        cesiumDebugTexturePoolInitialCapacity,
        cesiumDisplayName,
        cesiumEcefToUsdTransform,
        cesiumEnableFogCulling,
        cesiumEnableFrustumCulling,
        cesiumEnforceCulledScreenSpaceError,
        cesiumExcludeSelectedTiles,
        cesiumForbidHoles,
        cesiumGeoreferenceBinding,
        cesiumGeoreferenceOriginHeight,
        cesiumGeoreferenceOriginLatitude,
        cesiumGeoreferenceOriginLongitude,
        cesiumInvertSelection,
        cesiumIonAccessToken,
        cesiumIonAssetId,
        cesiumIonServerApiUrl,
        cesiumIonServerApplicationId,
        cesiumIonServerBinding,
        cesiumIonServerUrl,
        cesiumLayers,
        cesiumLoadingDescendantLimit,
        cesiumMainThreadLoadingTimeLimit,
        cesiumMaximumCachedBytes,
        cesiumMaximumLevel,
        cesiumMaximumScreenSpaceError,
        cesiumMaximumSimultaneousTileLoads,
        cesiumMaximumTextureSize,
        cesiumMinimumLevel,
        cesiumOverlayRenderMethod,
        cesiumPreloadAncestors,
        cesiumPreloadSiblings,
        cesiumProjectDefaultIonAccessToken,
        cesiumProjectDefaultIonAccessTokenId,
        cesiumRasterOverlayBinding,
        cesiumSelectedIonServer,
        cesiumShowCreditsOnScreen,
        cesiumSmoothNormals,
        cesiumSourceType,
        cesiumSubTileCacheBytes,
        cesiumSuspendUpdate,
        cesiumTileHeight,
        cesiumTileWidth,
        cesiumUrl,
        clip,
        ion,
        overlay,
        url
    })
{
}

TfStaticData<CesiumTokensType> CesiumTokens;

PXR_NAMESPACE_CLOSE_SCOPE
