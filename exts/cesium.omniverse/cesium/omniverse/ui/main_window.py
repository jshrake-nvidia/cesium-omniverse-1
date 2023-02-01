from ..bindings import ICesiumOmniverseInterface
import logging
import omni.kit.app as app
import omni.ui as ui
import webbrowser
from pathlib import Path
from typing import Optional

HELP_URL = "https://community.cesium.com/"
LEARN_URL = "https://cesium.com/learn/"
UPLOAD_URL = "https://ion.cesium.com/addasset"


class CesiumOmniverseMainWindow(ui.Window):
    """
    The main window for working with Cesium for Omniverse. Docked in the same area as "Stage".
    """

    WINDOW_NAME = "Cesium"
    MENU_PATH = f"Window/Cesium/{WINDOW_NAME}"

    def __init__(self, cesium_omniverse_interface: ICesiumOmniverseInterface, **kwargs):
        super().__init__(CesiumOmniverseMainWindow.WINDOW_NAME, **kwargs)
        manager = app.get_app().get_extension_manager()
        ext_id = manager.get_extension_id_by_module("cesium.omniverse")

        self._cesium_omniverse_interface = cesium_omniverse_interface
        self._logger = logging.getLogger(__name__)
        self._icon_path = Path(manager.get_extension_path(ext_id)).joinpath("icons")

        # Buttons aren't created until the build function is called.
        self._add_button: Optional[ui.Button] = None
        self._upload_button: Optional[ui.Button] = None
        self._token_button: Optional[ui.Button] = None
        self._learn_button: Optional[ui.Button] = None
        self._help_button: Optional[ui.Button] = None
        self._sign_out_button: Optional[ui.Button] = None

        self.frame.set_build_fn(self._build_fn)

    def destroy(self) -> None:
        super().destroy()

    def _build_fn(self):
        """Builds all UI components."""

        with ui.VStack():
            button_style = {
                "Button": {
                    "padding": 10.0,
                    "stack_direction": ui.Direction.TOP_TO_BOTTOM
                },
                "Button.Image": {
                    "alignment": ui.Alignment.CENTER,
                },
                "Button.Label": {
                    "alignment": ui.Alignment.CENTER_BOTTOM
                }
            }

            with ui.HStack(height=ui.Length(80, ui.UnitType.PIXEL)):
                self._add_button = ui.Button("Add", image_url=f"{self._icon_path}/FontAwesome/plus-solid.png",
                                             style=button_style, clicked_fn=self._add_button_clicked, enabled=False)
                self._upload_button = ui.Button("Upload",
                                                image_url=f"{self._icon_path}/FontAwesome/cloud-upload-alt-solid.png",
                                                style=button_style, clicked_fn=self._upload_button_clicked,
                                                enabled=False)
                self._token_button = ui.Button("Token", image_url=f"{self._icon_path}/FontAwesome/key-solid.png",
                                               style=button_style, clicked_fn=self._token_button_clicked)
                self._learn_button = ui.Button("Learn",
                                               image_url=f"{self._icon_path}/FontAwesome/book-reader-solid.png",
                                               style=button_style, clicked_fn=self._learn_button_clicked)
                self._help_button = ui.Button("Help",
                                              image_url=f"{self._icon_path}/FontAwesome/hands-helping-solid.png",
                                              style=button_style, clicked_fn=self._help_button_clicked)
                self._sign_out_button = ui.Button("Sign Out",
                                                  image_url=f"{self._icon_path}/FontAwesome/sign-out-alt-solid.png",
                                                  style=button_style, clicked_fn=self._sign_out_button_clicked,
                                                  enabled=False)
            ui.Label("TODO: The rest of this window.")

    def _add_button_clicked(self) -> None:
        if not self._add_button or not self._add_button.enabled:
            return

        # TODO: Implement CesiumMainWindow._add_button_clicked(self)

        pass

    def _upload_button_clicked(self) -> None:
        if not self._upload_button or not self._upload_button.enabled:
            return

        webbrowser.open(UPLOAD_URL)

    def _token_button_clicked(self) -> None:
        if not self._token_button:
            return

        # TODO: Implement CesiumMainWindow._token_button_clicked(self)

        pass

    def _learn_button_clicked(self) -> None:
        if not self._learn_button:
            return

        webbrowser.open(LEARN_URL)

    def _help_button_clicked(self) -> None:
        if not self._help_button:
            return

        webbrowser.open(HELP_URL)

    def _sign_out_button_clicked(self) -> None:
        if not self._sign_out_button or not self._upload_button.enabled:
            return

        # TODO: Implement CesiumMainWindow._sign_out_button_clicked(self)

        pass