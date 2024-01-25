#include "cesium/omniverse/AssetRegistry.h"

#include "cesium/omniverse/Context.h"
#include "cesium/omniverse/CppUtil.h"
#include "cesium/omniverse/OmniCartographicPolygon.h"
#include "cesium/omniverse/OmniData.h"
#include "cesium/omniverse/OmniGeoreference.h"
#include "cesium/omniverse/OmniGlobeAnchor.h"
#include "cesium/omniverse/OmniIonImagery.h"
#include "cesium/omniverse/OmniIonServer.h"
#include "cesium/omniverse/OmniPolygonImagery.h"
#include "cesium/omniverse/OmniTileset.h"
#include "cesium/omniverse/UsdUtil.h"
#include "cesium/omniverse/Viewport.h"

namespace cesium::omniverse {

AssetRegistry::AssetRegistry(Context* pContext)
    : _pContext(pContext) {}

AssetRegistry::~AssetRegistry() = default;

void AssetRegistry::onUpdateFrame(const gsl::span<const Viewport>& viewports) {
    for (const auto& pTileset : _tilesets) {
        pTileset->onUpdateFrame(viewports);
    }
}

OmniData& AssetRegistry::addData(const pxr::SdfPath& path) {
    return *_datas.insert(_datas.end(), std::make_unique<OmniData>(_pContext, path))->get();
}

void AssetRegistry::removeData(const pxr::SdfPath& path) {
    CppUtil::eraseIf(_datas, [&path](const auto& pData) { return pData->getPath() == path; });
}

OmniData* AssetRegistry::getData(const pxr::SdfPath& path) const {
    for (const auto& pData : _datas) {
        if (pData->getPath() == path) {
            return pData.get();
        }
    }

    return nullptr;
}

OmniData* AssetRegistry::getFirstData() const {
    if (_datas.empty()) {
        return nullptr;
    }

    return _datas.front().get();
}

OmniTileset& AssetRegistry::addTileset(const pxr::SdfPath& path) {
    return *_tilesets.insert(_tilesets.end(), std::make_unique<OmniTileset>(_pContext, path, _tilesetId++))->get();
}

void AssetRegistry::removeTileset(const pxr::SdfPath& path) {
    CppUtil::eraseIf(_tilesets, [&path](const auto& pTileset) { return pTileset->getPath() == path; });
}

OmniTileset* AssetRegistry::getTileset(const pxr::SdfPath& path) const {
    for (const auto& pTileset : _tilesets) {
        if (pTileset->getPath() == path) {
            return pTileset.get();
        }
    }

    return nullptr;
}

const std::vector<std::unique_ptr<OmniTileset>>& AssetRegistry::getTilesets() const {
    return _tilesets;
}

OmniIonImagery& AssetRegistry::addIonImagery(const pxr::SdfPath& path) {
    return *_ionImageries.insert(_ionImageries.end(), std::make_unique<OmniIonImagery>(_pContext, path))->get();
}

void AssetRegistry::removeIonImagery(const pxr::SdfPath& path) {
    CppUtil::eraseIf(_ionImageries, [&path](const auto& pIonImagery) { return pIonImagery->getPath() == path; });
}

OmniIonImagery* AssetRegistry::getIonImagery(const pxr::SdfPath& path) const {
    for (const auto& pIonImagery : _ionImageries) {
        if (pIonImagery->getPath() == path) {
            return pIonImagery.get();
        }
    }

    return nullptr;
}

OmniIonImagery* AssetRegistry::getIonImageryByIonAssetId(int64_t ionAssetId) const {
    for (const auto& pIonImagery : _ionImageries) {
        if (pIonImagery->getIonAssetId() == ionAssetId) {
            return pIonImagery.get();
        }
    }

    return nullptr;
}

const std::vector<std::unique_ptr<OmniIonImagery>>& AssetRegistry::getIonImageries() const {
    return _ionImageries;
}

OmniPolygonImagery& AssetRegistry::addPolygonImagery(const pxr::SdfPath& path) {
    return *_polygonImageries.insert(_polygonImageries.end(), std::make_unique<OmniPolygonImagery>(_pContext, path))
                ->get();
}

void AssetRegistry::removePolygonImagery(const pxr::SdfPath& path) {
    CppUtil::eraseIf(
        _polygonImageries, [&path](const auto& pPolygonImagery) { return pPolygonImagery->getPath() == path; });
}

OmniPolygonImagery* AssetRegistry::getPolygonImagery(const pxr::SdfPath& path) const {
    for (const auto& pPolygonImagery : _polygonImageries) {
        if (pPolygonImagery->getPath() == path) {
            return pPolygonImagery.get();
        }
    }

    return nullptr;
}

const std::vector<std::unique_ptr<OmniPolygonImagery>>& AssetRegistry::getPolygonImageries() const {
    return _polygonImageries;
}

OmniImagery* AssetRegistry::getImagery(const pxr::SdfPath& path) const {
    const auto pIonImagery = getIonImagery(path);

    if (pIonImagery) {
        return pIonImagery;
    }

    const auto pPolygonImagery = getPolygonImagery(path);

    if (pPolygonImagery) {
        return pPolygonImagery;
    }

    return nullptr;
}

OmniGeoreference& AssetRegistry::addGeoreference(const pxr::SdfPath& path) {
    return *_georeferences.insert(_georeferences.end(), std::make_unique<OmniGeoreference>(_pContext, path))->get();
}

void AssetRegistry::removeGeoreference(const pxr::SdfPath& path) {
    CppUtil::eraseIf(_georeferences, [&path](const auto& pGeoreference) { return pGeoreference->getPath() == path; });
}

OmniGeoreference* AssetRegistry::getGeoreference(const pxr::SdfPath& path) const {
    for (const auto& pGeoreference : _georeferences) {
        if (pGeoreference->getPath() == path) {
            return pGeoreference.get();
        }
    }

    return nullptr;
}

const std::vector<std::unique_ptr<OmniGeoreference>>& AssetRegistry::getGeoreferences() const {
    return _georeferences;
}

OmniGlobeAnchor& AssetRegistry::addGlobeAnchor(const pxr::SdfPath& path) {
    return *_globeAnchors.insert(_globeAnchors.end(), std::make_unique<OmniGlobeAnchor>(_pContext, path))->get();
}

void AssetRegistry::removeGlobeAnchor(const pxr::SdfPath& path) {
    CppUtil::eraseIf(_globeAnchors, [&path](const auto& pGlobeAnchor) { return pGlobeAnchor->getPath() == path; });
}

OmniGlobeAnchor* AssetRegistry::getGlobeAnchor(const pxr::SdfPath& path) const {
    for (const auto& pGlobeAnchor : _globeAnchors) {
        if (pGlobeAnchor->getPath() == path) {
            return pGlobeAnchor.get();
        }
    }

    return nullptr;
}
const std::vector<std::unique_ptr<OmniGlobeAnchor>>& AssetRegistry::getGlobeAnchors() const {
    return _globeAnchors;
}

OmniIonServer& AssetRegistry::addIonServer(const pxr::SdfPath& path) {
    return *_ionServers.insert(_ionServers.end(), std::make_unique<OmniIonServer>(_pContext, path))->get();
}

void AssetRegistry::removeIonServer(const pxr::SdfPath& path) {
    CppUtil::eraseIf(_ionServers, [&path](const auto& pIonServer) { return pIonServer->getPath() == path; });
}

OmniIonServer* AssetRegistry::getIonServer(const pxr::SdfPath& path) const {
    for (const auto& pIonServer : _ionServers) {
        if (pIonServer->getPath() == path) {
            return pIonServer.get();
        }
    }

    return nullptr;
}

const std::vector<std::unique_ptr<OmniIonServer>>& AssetRegistry::getIonServers() const {
    return _ionServers;
}

OmniIonServer* AssetRegistry::getFirstIonServer() const {
    if (_ionServers.empty()) {
        return nullptr;
    }

    return _ionServers.front().get();
}

OmniCartographicPolygon& AssetRegistry::addCartographicPolygon(const pxr::SdfPath& path) {
    return *_cartographicPolygons
                .insert(_cartographicPolygons.end(), std::make_unique<OmniCartographicPolygon>(_pContext, path))
                ->get();
}

void AssetRegistry::removeCartographicPolygon(const pxr::SdfPath& path) {
    CppUtil::eraseIf(_cartographicPolygons, [&path](const auto& pCartographicPolygon) {
        return pCartographicPolygon->getPath() == path;
    });
}

OmniCartographicPolygon* AssetRegistry::getCartographicPolygon(const pxr::SdfPath& path) const {
    for (const auto& pCartographicPolygon : _cartographicPolygons) {
        if (pCartographicPolygon->getPath() == path) {
            return pCartographicPolygon.get();
        }
    }

    return nullptr;
}

const std::vector<std::unique_ptr<OmniCartographicPolygon>>& AssetRegistry::getCartographicPolygons() const {
    return _cartographicPolygons;
}

AssetType AssetRegistry::getAssetType(const pxr::SdfPath& path) const {
    if (getData(path)) {
        return AssetType::DATA;
    } else if (getTileset(path)) {
        return AssetType::TILESET;
    } else if (getIonImagery(path)) {
        return AssetType::ION_IMAGERY;
    } else if (getPolygonImagery(path)) {
        return AssetType::POLYGON_IMAGERY;
    } else if (getGeoreference(path)) {
        return AssetType::GEOREFERENCE;
    } else if (getIonServer(path)) {
        return AssetType::ION_SERVER;
    } else if (getCartographicPolygon(path)) {
        return AssetType::CARTOGRAPHIC_POLYGON;
    } else if (getGlobeAnchor(path)) {
        // Globe anchor needs to be checked last since prim types take precedence over API schemas
        return AssetType::GLOBE_ANCHOR;
    } else {
        return AssetType::OTHER;
    }
}

bool AssetRegistry::hasAsset(const pxr::SdfPath& path) const {
    return getAssetType(path) != AssetType::OTHER;
}

void AssetRegistry::clear() {
    _datas.clear();
    _tilesets.clear();
    _ionImageries.clear();
    _polygonImageries.clear();
    _georeferences.clear();
    _globeAnchors.clear();
    _ionServers.clear();
    _cartographicPolygons.clear();
}

} // namespace cesium::omniverse
