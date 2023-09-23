"""Export the funtions to python"""
from ctypes import windll
from pathlib import Path

material = windll.LoadLibrary(str(Path(__file__).parent / \
                                f"win32material.dll"))
style = windll.LoadLibrary(str(Path(__file__).parent / \
                               f"win32style.dll"))

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
    hwnd: int = 0, theme: bool = True, micaalt: bool = True, extend: bool = True
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
        raise OSError("Use Windows 11 to apply mica effect to the win32 application")

    if getwindowsversion().build < 22523:
        material.ApplyUndocumentMica(hwnd, theme, micaalt, extend)
    else:
        material.ApplyDocumentMica(hwnd, theme, micaalt, extend)


def ApplyAcrylic(hwnd: int = 0, theme: bool = True, hexcolor: int = 0) -> None:
    """Apply acrylic effect to Win32 Applications
    Args:
        hwnd(int): The target window's hwnd
        theme(bool):
            false -> light
            true -> dark
        hexcolor(int): The effect's hexcolor
    """
    material.ApplyAcrylic(hwnd, theme, hexcolor)


def ApplyBlur(hwnd: int = 0, theme: bool = True, hexcolor: int = 0) -> None:
    """Apply Blur effect to Win32 Applications
    Args:
        hwnd(int): The target window's hwnd
        theme(bool):
            false -> light
            true -> dark
        hexcolor(int): The effect's hexcolor
    """
    material.ApplyBlur(hwnd, theme, hexcolor)

def ChangeTitlebarColor(hwnd: int, color: str) -> None:
    color = f"{color[5:7]}{color[3:5]}{color[1:3]}"
    style.ChangeTitlebarColor(hwnd, int(color, base = 16))

def ChangeBorderColor(hwnd: int, color: str) -> None:
    color = f"{color[5:7]}{color[3:5]}{color[1:3]}"
    style.ChangeBorderColor(hwnd, int(color, base = 16))

def ChangeTitleColor(hwnd: int, color: str) -> None:
    color = f"{color[5:7]}{color[3:5]}{color[1:3]}"
    style.ChangeTitleColor(hwnd, int(color, base = 16))

def SetBorderType(hwnd: int, type: BORDERTYPE | int) -> None:
    style.SetBorderType(hwnd, type)

def ApplyDarkMode(hwnd: int) -> None:
    style.ApplyDarkMode(hwnd)