"""Export the funtions to python"""
from ctypes import windll
from pathlib import Path

style = windll.LoadLibrary(str(Path(__file__).parent / f"win32style.dll"))


class MICATHEME:
    LIGHT: bool = False
    DARK: bool = True


class MICAMODE:
    DEFAULT: bool = False
    ALT: bool = True


class BORDERTYPE:
    RECTANGULAR: int = 1
    ROUND: int = 2
    SMALLROUND: int = 3


def ApplyMica(
    hwnd: int, theme: bool = True, micaalt: bool = True, extend: bool = True
) -> None:
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
        raise OSError("Use Windows 11 to apply mica effect")

    if getwindowsversion().build < 22523:
        style.ApplyUndocumentMica(hwnd, theme, micaalt, extend)
    else:
        style.ApplyDocumentMica(hwnd, theme, micaalt, extend)


def ApplyAcrylic(hwnd: int, extend: bool = False, hexcolor: int | bool = False) -> None:
    """Apply acrylic effect to Win32 Applications
    Args:
        hwnd(int): The target window's hwnd
        hexcolor(int): The effect's hexcolor
    """
    style.ApplyAcrylic(hwnd, extend, hexcolor)


def ChangeTitlebarColor(hwnd: int, color: str) -> None:
    color = f"{color[5:7]}{color[3:5]}{color[1:3]}"
    style.ChangeTitlebarColor(hwnd, int(color, base=16))


def ChangeBorderColor(hwnd: int, color: str) -> None:
    color = f"{color[5:7]}{color[3:5]}{color[1:3]}"
    style.ChangeBorderColor(hwnd, int(color, base=16))


def ChangeTitleColor(hwnd: int, color: str) -> None:
    color = f"{color[5:7]}{color[3:5]}{color[1:3]}"
    style.ChangeTitleColor(hwnd, int(color, base=16))


def SetBorderType(hwnd: int, type: BORDERTYPE | int) -> None:
    style.SetBorderType(hwnd, type)


def ApplyDarkMode(hwnd: int) -> None:
    style.ApplyDarkMode(hwnd)
