"""Export the funtions to python"""
from ctypes import windll
from pathlib import Path

plugin = windll.LoadLibrary(str(Path(__file__).parent / "win32material.dll"))

class MICATHEME:
    LIGHT: bool = False
    DARK: bool = True


class MICAMODE:
    DEFAULT: bool = False
    ALT: bool = True


def ApplyMica(hwnd: int = 0, theme: bool = True, micaalt: bool = True, extend: bool = True) -> None:
    """Apply mica effect to Win32 Applications
    Args:
        hwnd(int): The target window's hwnd
        theme(bool):
            false -> light
            true -> dark
        micaalt(bool):
            false -> default
            true -> alt
        extend(bool):
            false -> only apply to titlebar
            true -> extend to the window
    """
    from sys import getwindowsversion
    if getwindowsversion().build < 22000:
        raise OSError("Use Windows 11 to apply mica effect to the win32 application")

    if getwindowsversion().build < 22523:
        plugin.ApplyUndocumentMica(hwnd, theme, micaalt, extend)
    else:
        plugin.ApplyDocumentMica(hwnd, theme, micaalt, extend)

def ApplyAcrylic(hwnd: int = 0, theme: bool = True, hexcolor: int = 0) -> None:
    """Apply acrylic effect to Win32 Applications
    Args:
        hwnd(int): The target window's hwnd
        theme(bool):
            false -> light
            true -> dark
        hexcolor(int): The effect's hexcolor
    """
    plugin.ApplyAcrylic(hwnd, theme, hexcolor)

def ApplyBlur(hwnd: int = 0, theme: bool = True, hexcolor: int = 0) -> None:
    """Apply Blur effect to Win32 Applications
    Args:
        hwnd(int): The target window's hwnd
        theme(bool):
            false -> light
            true -> dark
        hexcolor(int): The effect's hexcolor
    """
    plugin.ApplyBlur(hwnd, theme, hexcolor)