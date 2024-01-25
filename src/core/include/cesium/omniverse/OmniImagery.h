#pragma once

#include <pxr/usd/sdf/path.h>

namespace CesiumRasterOverlays {
class RasterOverlay;
}

namespace cesium::omniverse {

class Context;
enum class FabricOverlayRenderMethod;

class OmniImagery {
  public:
    OmniImagery(Context* pContext, const pxr::SdfPath& path);
    virtual ~OmniImagery() = default;
    OmniImagery(const OmniImagery&) = delete;
    OmniImagery& operator=(const OmniImagery&) = delete;
    OmniImagery(OmniImagery&&) noexcept = default;
    OmniImagery& operator=(OmniImagery&&) noexcept = default;

    [[nodiscard]] const pxr::SdfPath& getPath() const;
    [[nodiscard]] bool getShowCreditsOnScreen() const;
    [[nodiscard]] double getAlpha() const;
    [[nodiscard]] FabricOverlayRenderMethod getOverlayRenderMethod() const;

    [[nodiscard]] virtual CesiumRasterOverlays::RasterOverlay* getRasterOverlay() const = 0;
    virtual void reload() = 0;

  protected:
    Context* _pContext;
    pxr::SdfPath _path;
};
} // namespace cesium::omniverse
