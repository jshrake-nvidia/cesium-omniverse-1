#pragma once

#include "CesiumOmniverseAbi.h"

#include <pxr/pxr.h>

#include <cstdint>

PXR_NAMESPACE_OPEN_SCOPE
class GfMatrix4d;
PXR_NAMESPACE_CLOSE_SCOPE

namespace Cesium {

/**
 * @brief Call this before any tilesets are created.
 *
 * @param cesiumMemLocation The folder containing mem.cesium
 */
CESIUM_OMNI_EXPORT_C_FUNCTION(void)
initialize(const char* cesiumMemLocation) CESIUM_OMNI_NOEXCEPT;

/**
 * @brief Call this to free resources on program exist.
 */
CESIUM_OMNI_EXPORT_C_FUNCTION(void)
finalize() CESIUM_OMNI_NOEXCEPT;

/**
 * @brief Adds a tileset from url.
 *
 * @param stage The USD stage id
 * @param url The tileset url
 * @returns The tileset id. Returns -1 on error.
 */
CESIUM_OMNI_EXPORT_C_FUNCTION(int)
addTilesetUrl(long stageId, const char* url) CESIUM_OMNI_NOEXCEPT;

/**
 * @brief Adds a tileset from ion.
 *
 * @param stage The USD stage id
 * @param ionId The ion asset id
 * @param ionToken The ion access token
 * @returns The tileset id. Returns -1 on error.
 */
CESIUM_OMNI_EXPORT_C_FUNCTION(int)
addTilesetIon(long stageId, int64_t ionId, const char* ionToken) CESIUM_OMNI_NOEXCEPT;

/**
 * @brief Removes a tileset from the scene.
 *
 * @param tileset The tileset id. If there's no tileset with this id nothing happens.
 */
CESIUM_OMNI_EXPORT_C_FUNCTION(void)
removeTileset(int tileset) CESIUM_OMNI_NOEXCEPT;

/**
 * @brief Adds a raster overlay from ion.
 *
 * @param tileset The tileset id
 * @param name The user-given name of this overlay layer
 * @param ionId The asset ID
 * @param ionToken The access token
 */
CESIUM_OMNI_EXPORT_C_FUNCTION(void)
addIonRasterOverlay(int tileset, const char* name, int64_t ionId, const char* ionToken) CESIUM_OMNI_NOEXCEPT;

/**
 * @brief Updates the tileset this frame.
 *
 * @param tileset The tileset id. If there's no tileset with this id nothing happens.
 * @param viewMatrix The view matrix.
 * @param projMatrix The projection matrix.
 * @param width The screen width
 * @param height The screen height
 */
CESIUM_OMNI_EXPORT_C_FUNCTION(void)
updateFrame(
    int tileset,
    const pxr::GfMatrix4d* viewMatrix,
    const pxr::GfMatrix4d* projMatrix,
    double width,
    double height) CESIUM_OMNI_NOEXCEPT;

/**
 * @brief Sets the georeference origin based on the WGS84 ellipsoid.
 *
 * @param longitude The longitude in degrees
 * @param latitude The latitude in degrees
 * @param height The height in meters
 */
CESIUM_OMNI_EXPORT_C_FUNCTION(void)
setGeoreferenceOrigin(double longitude, double latitude, double height) CESIUM_OMNI_NOEXCEPT;

} // namespace Cesium