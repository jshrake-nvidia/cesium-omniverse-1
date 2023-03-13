import logging
import omni.kit.window.property

from ..bindings import ICesiumOmniverseInterface
from .attributes import CesiumDataSchemaAttributesWidget


class CesiumAttributesWidgetController:
    """
    This is designed as a helpful function for separating out the registration and
    unregistration of Cesium's attributes widgets.
    """

    def __init__(self, _cesium_omniverse_interface: ICesiumOmniverseInterface):
        self._cesium_omniverse_interface = _cesium_omniverse_interface
        self._logger = logging.getLogger(__name__)

        self._register_data_attributes_widget()

    def destroy(self):
        self._unregister_data_attributes_widget()

    @staticmethod
    def _register_data_attributes_widget():
        window = omni.kit.window.property.get_window()
        if window is not None:
            window.register_widget("prim", "cesiumData", CesiumDataSchemaAttributesWidget())

    @staticmethod
    def _unregister_data_attributes_widget():
        window = omni.kit.window.property.get_window()
        if window is not None:
            window.unregister_widget("prim", "cesiumData")