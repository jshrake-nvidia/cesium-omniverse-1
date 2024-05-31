from typing import Any, ClassVar

import Boost.Python
import pxr.Usd
import pxr.UsdGeom

__MFB_FULL_PACKAGE_NAME: str

class Data(pxr.Usd.Typed):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def CreateDebugDisableGeometryPoolAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateDebugDisableGeoreferencingAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateDebugDisableMaterialPoolAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateDebugDisableMaterialsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateDebugDisableTexturePoolAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateDebugDisableTexturesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateDebugGeometryPoolInitialCapacityAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateDebugMaterialPoolInitialCapacityAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateDebugRandomColorsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateDebugTexturePoolInitialCapacityAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateSelectedIonServerRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Define(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Get(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDebugDisableGeometryPoolAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDebugDisableGeoreferencingAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDebugDisableMaterialPoolAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDebugDisableMaterialsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDebugDisableTexturePoolAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDebugDisableTexturesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDebugGeometryPoolInitialCapacityAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDebugMaterialPoolInitialCapacityAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDebugRandomColorsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDebugTexturePoolInitialCapacityAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSchemaAttributeNames(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSelectedIonServerRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def _GetStaticTfType(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...

class Georeference(pxr.Usd.Typed):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def CreateEcefToUsdTransformAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateGeoreferenceOriginHeightAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateGeoreferenceOriginLatitudeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateGeoreferenceOriginLongitudeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Define(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Get(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetEcefToUsdTransformAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetGeoreferenceOriginHeightAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetGeoreferenceOriginLatitudeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetGeoreferenceOriginLongitudeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSchemaAttributeNames(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def _GetStaticTfType(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...

class GlobeAnchorAPI(pxr.Usd.APISchemaBase):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def Apply(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CanApply(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateAdjustOrientationForGlobeWhenMovingAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateAnchorHeightAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateAnchorLatitudeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateAnchorLongitudeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateDetectTransformChangesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateGeoreferenceBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreatePositionAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Get(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetAdjustOrientationForGlobeWhenMovingAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetAnchorHeightAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetAnchorLatitudeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetAnchorLongitudeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDetectTransformChangesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetGeoreferenceBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetPositionAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSchemaAttributeNames(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def _GetStaticTfType(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...

class IonRasterOverlay(RasterOverlay):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def CreateIonAccessTokenAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateIonAssetIdAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateIonServerBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Define(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Get(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetIonAccessTokenAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetIonAssetIdAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetIonServerBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSchemaAttributeNames(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def _GetStaticTfType(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...

class IonServer(pxr.Usd.Typed):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def CreateDisplayNameAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateIonServerApiUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateIonServerApplicationIdAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateIonServerUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateProjectDefaultIonAccessTokenAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateProjectDefaultIonAccessTokenIdAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Define(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Get(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetDisplayNameAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetIonServerApiUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetIonServerApplicationIdAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetIonServerUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetProjectDefaultIonAccessTokenAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetProjectDefaultIonAccessTokenIdAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSchemaAttributeNames(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def _GetStaticTfType(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...

class PolygonRasterOverlay(RasterOverlay):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def CreateCartographicPolygonBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateCesiumOverlayRenderMethodAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateExcludeSelectedTilesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateInvertSelectionAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Define(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Get(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetCartographicPolygonBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetCesiumOverlayRenderMethodAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetExcludeSelectedTilesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetInvertSelectionAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSchemaAttributeNames(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def _GetStaticTfType(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...

class RasterOverlay(pxr.Usd.Typed):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def CreateAlphaAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMaximumScreenSpaceErrorAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMaximumSimultaneousTileLoadsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMaximumTextureSizeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateOverlayRenderMethodAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateShowCreditsOnScreenAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateSubTileCacheBytesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Get(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetAlphaAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMaximumScreenSpaceErrorAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMaximumSimultaneousTileLoadsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMaximumTextureSizeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetOverlayRenderMethodAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSchemaAttributeNames(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetShowCreditsOnScreenAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSubTileCacheBytesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def _GetStaticTfType(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...

class TileMapServiceRasterOverlay(RasterOverlay):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def CreateMaximumZoomLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMinimumZoomLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateSpecifyZoomLevelsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Define(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Get(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMaximumZoomLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMinimumZoomLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSchemaAttributeNames(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSpecifyZoomLevelsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def _GetStaticTfType(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...

class Tileset(pxr.UsdGeom.Gprim):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def CreateCulledScreenSpaceErrorAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateEnableFogCullingAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateEnableFrustumCullingAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateEnforceCulledScreenSpaceErrorAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateForbidHolesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateGeoreferenceBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateIonAccessTokenAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateIonAssetIdAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateIonServerBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateLoadingDescendantLimitAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMainThreadLoadingTimeLimitAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMaximumCachedBytesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMaximumScreenSpaceErrorAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMaximumSimultaneousTileLoadsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreatePointSizeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreatePreloadAncestorsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreatePreloadSiblingsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateRasterOverlayBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateShowCreditsOnScreenAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateSmoothNormalsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateSourceTypeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateSuspendUpdateAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Define(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Get(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetCulledScreenSpaceErrorAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetEnableFogCullingAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetEnableFrustumCullingAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetEnforceCulledScreenSpaceErrorAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetForbidHolesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetGeoreferenceBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetIonAccessTokenAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetIonAssetIdAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetIonServerBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetLoadingDescendantLimitAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMainThreadLoadingTimeLimitAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMaximumCachedBytesAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMaximumScreenSpaceErrorAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMaximumSimultaneousTileLoadsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetPointSizeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetPreloadAncestorsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetPreloadSiblingsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetRasterOverlayBindingRel(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSchemaAttributeNames(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetShowCreditsOnScreenAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSmoothNormalsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSourceTypeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSuspendUpdateAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def _GetStaticTfType(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...

class Tokens(Boost.Python.instance):
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def __reduce__(cls) -> Any: ...
    @property
    def cesiumAlpha(self) -> Any: ...
    @property
    def cesiumAnchorAdjustOrientationForGlobeWhenMoving(self) -> Any: ...
    @property
    def cesiumAnchorDetectTransformChanges(self) -> Any: ...
    @property
    def cesiumAnchorGeoreferenceBinding(self) -> Any: ...
    @property
    def cesiumAnchorHeight(self) -> Any: ...
    @property
    def cesiumAnchorLatitude(self) -> Any: ...
    @property
    def cesiumAnchorLongitude(self) -> Any: ...
    @property
    def cesiumAnchorPosition(self) -> Any: ...
    @property
    def cesiumBaseUrl(self) -> Any: ...
    @property
    def cesiumCartographicPolygonBinding(self) -> Any: ...
    @property
    def cesiumCulledScreenSpaceError(self) -> Any: ...
    @property
    def cesiumDebugDisableGeometryPool(self) -> Any: ...
    @property
    def cesiumDebugDisableGeoreferencing(self) -> Any: ...
    @property
    def cesiumDebugDisableMaterialPool(self) -> Any: ...
    @property
    def cesiumDebugDisableMaterials(self) -> Any: ...
    @property
    def cesiumDebugDisableTexturePool(self) -> Any: ...
    @property
    def cesiumDebugDisableTextures(self) -> Any: ...
    @property
    def cesiumDebugGeometryPoolInitialCapacity(self) -> Any: ...
    @property
    def cesiumDebugMaterialPoolInitialCapacity(self) -> Any: ...
    @property
    def cesiumDebugRandomColors(self) -> Any: ...
    @property
    def cesiumDebugTexturePoolInitialCapacity(self) -> Any: ...
    @property
    def cesiumDisplayName(self) -> Any: ...
    @property
    def cesiumEast(self) -> Any: ...
    @property
    def cesiumEcefToUsdTransform(self) -> Any: ...
    @property
    def cesiumEnableFogCulling(self) -> Any: ...
    @property
    def cesiumEnableFrustumCulling(self) -> Any: ...
    @property
    def cesiumEnforceCulledScreenSpaceError(self) -> Any: ...
    @property
    def cesiumExcludeSelectedTiles(self) -> Any: ...
    @property
    def cesiumForbidHoles(self) -> Any: ...
    @property
    def cesiumFormat(self) -> Any: ...
    @property
    def cesiumGeoreferenceBinding(self) -> Any: ...
    @property
    def cesiumGeoreferenceOriginHeight(self) -> Any: ...
    @property
    def cesiumGeoreferenceOriginLatitude(self) -> Any: ...
    @property
    def cesiumGeoreferenceOriginLongitude(self) -> Any: ...
    @property
    def cesiumInvertSelection(self) -> Any: ...
    @property
    def cesiumIonAccessToken(self) -> Any: ...
    @property
    def cesiumIonAssetId(self) -> Any: ...
    @property
    def cesiumIonServerApiUrl(self) -> Any: ...
    @property
    def cesiumIonServerApplicationId(self) -> Any: ...
    @property
    def cesiumIonServerBinding(self) -> Any: ...
    @property
    def cesiumIonServerUrl(self) -> Any: ...
    @property
    def cesiumLayer(self) -> Any: ...
    @property
    def cesiumLayers(self) -> Any: ...
    @property
    def cesiumLoadingDescendantLimit(self) -> Any: ...
    @property
    def cesiumMainThreadLoadingTimeLimit(self) -> Any: ...
    @property
    def cesiumMaximumCachedBytes(self) -> Any: ...
    @property
    def cesiumMaximumLevel(self) -> Any: ...
    @property
    def cesiumMaximumScreenSpaceError(self) -> Any: ...
    @property
    def cesiumMaximumSimultaneousTileLoads(self) -> Any: ...
    @property
    def cesiumMaximumTextureSize(self) -> Any: ...
    @property
    def cesiumMaximumZoomLevel(self) -> Any: ...
    @property
    def cesiumMinimumLevel(self) -> Any: ...
    @property
    def cesiumMinimumZoomLevel(self) -> Any: ...
    @property
    def cesiumNorth(self) -> Any: ...
    @property
    def cesiumOverlayRenderMethod(self) -> Any: ...
    @property
    def cesiumPointSize(self) -> Any: ...
    @property
    def cesiumPreloadAncestors(self) -> Any: ...
    @property
    def cesiumPreloadSiblings(self) -> Any: ...
    @property
    def cesiumProjectDefaultIonAccessToken(self) -> Any: ...
    @property
    def cesiumProjectDefaultIonAccessTokenId(self) -> Any: ...
    @property
    def cesiumRasterOverlayBinding(self) -> Any: ...
    @property
    def cesiumRootTilesX(self) -> Any: ...
    @property
    def cesiumRootTilesY(self) -> Any: ...
    @property
    def cesiumSelectedIonServer(self) -> Any: ...
    @property
    def cesiumShowCreditsOnScreen(self) -> Any: ...
    @property
    def cesiumSmoothNormals(self) -> Any: ...
    @property
    def cesiumSourceType(self) -> Any: ...
    @property
    def cesiumSouth(self) -> Any: ...
    @property
    def cesiumSpecifyTileMatrixSetLabels(self) -> Any: ...
    @property
    def cesiumSpecifyTilingScheme(self) -> Any: ...
    @property
    def cesiumSpecifyZoomLevels(self) -> Any: ...
    @property
    def cesiumStyle(self) -> Any: ...
    @property
    def cesiumSubTileCacheBytes(self) -> Any: ...
    @property
    def cesiumSuspendUpdate(self) -> Any: ...
    @property
    def cesiumTileHeight(self) -> Any: ...
    @property
    def cesiumTileMatrixSetId(self) -> Any: ...
    @property
    def cesiumTileMatrixSetLabelPrefix(self) -> Any: ...
    @property
    def cesiumTileMatrixSetLabels(self) -> Any: ...
    @property
    def cesiumTileWidth(self) -> Any: ...
    @property
    def cesiumUrl(self) -> Any: ...
    @property
    def cesiumUseWebMercatorProjection(self) -> Any: ...
    @property
    def cesiumWest(self) -> Any: ...
    @property
    def clip(self) -> Any: ...
    @property
    def ion(self) -> Any: ...
    @property
    def overlay(self) -> Any: ...
    @property
    def url(self) -> Any: ...

class WebMapServiceRasterOverlay(RasterOverlay):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def CreateBaseUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateLayersAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMaximumLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMinimumLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateTileHeightAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateTileWidthAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Define(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Get(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetBaseUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetLayersAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMaximumLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMinimumLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSchemaAttributeNames(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetTileHeightAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetTileWidthAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def _GetStaticTfType(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...

class WebMapTileServiceRasterOverlay(RasterOverlay):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def CreateEastAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateFormatAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateLayerAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMaximumZoomLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateMinimumZoomLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateNorthAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateRootTilesXAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateRootTilesYAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateSouthAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateSpecifyTileMatrixSetLabelsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateSpecifyTilingSchemeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateSpecifyZoomLevelsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateStyleAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateTileMatrixSetIdAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateTileMatrixSetLabelPrefixAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateTileMatrixSetLabelsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateUseWebMercatorProjectionAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def CreateWestAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Define(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def Get(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetEastAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetFormatAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetLayerAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMaximumZoomLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetMinimumZoomLevelAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetNorthAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetRootTilesXAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetRootTilesYAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSchemaAttributeNames(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSouthAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSpecifyTileMatrixSetLabelsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSpecifyTilingSchemeAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetSpecifyZoomLevelsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetStyleAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetTileMatrixSetIdAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetTileMatrixSetLabelPrefixAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetTileMatrixSetLabelsAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetUrlAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetUseWebMercatorProjectionAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def GetWestAttr(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def _GetStaticTfType(cls, *args, **kwargs) -> Any: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...

class _CanApplyResult(Boost.Python.instance):
    __instance_size__: ClassVar[int] = ...
    @classmethod
    def __init__(cls, *args, **kwargs) -> None: ...
    @classmethod
    def __bool__(cls) -> bool: ...
    @classmethod
    def __eq__(cls, other) -> bool: ...
    @classmethod
    def __getitem__(cls, index) -> Any: ...
    @classmethod
    def __ne__(cls, other) -> bool: ...
    @classmethod
    def __reduce__(cls) -> Any: ...
    @property
    def whyNot(self) -> Any: ...
