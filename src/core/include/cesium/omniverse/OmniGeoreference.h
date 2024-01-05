#pragma once

#include <CesiumGeospatial/Ellipsoid.h>
#include <CesiumGeospatial/LocalHorizontalCoordinateSystem.h>
#include <pxr/usd/sdf/path.h>

namespace CesiumGeospatial {
class Cartographic;
class LocalHorizontalCoordinateSystem;
} // namespace CesiumGeospatial

namespace cesium::omniverse {

class Context;

class OmniGeoreference {
  public:
    OmniGeoreference(Context* pContext, const PXR_NS::SdfPath& path);
    ~OmniGeoreference() = default;
    OmniGeoreference(const OmniGeoreference&) = delete;
    OmniGeoreference& operator=(const OmniGeoreference&) = delete;
    OmniGeoreference(OmniGeoreference&&) noexcept = default;
    OmniGeoreference& operator=(OmniGeoreference&&) noexcept = default;

    [[nodiscard]] const PXR_NS::SdfPath& getPath() const;
    [[nodiscard]] CesiumGeospatial::Cartographic getOrigin() const;
    [[nodiscard]] const CesiumGeospatial::Ellipsoid& getEllipsoid() const;
    [[nodiscard]] CesiumGeospatial::LocalHorizontalCoordinateSystem getLocalCoordinateSystem() const;

  private:
    Context* _pContext;
    PXR_NS::SdfPath _path;
    CesiumGeospatial::Ellipsoid _ellipsoid;
};
} // namespace cesium::omniverse
