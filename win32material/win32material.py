"""Define different materials and functions for win32 applications"""

from __future__ import annotations

from ctypes import (POINTER, Structure, byref, c_int,
                    pointer, sizeof, windll)
from ctypes.wintypes import HWND, DWORD, ULONG
from functools import partial
from sys import getwindowsversion

dwmapi = windll.dwmapi
user32 = windll.user32


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


class AccentPolicy(Structure):
    _fields_ = [
        ("AccentState", DWORD),
        ("AccentFlags", DWORD),
        ("GradientColor", DWORD),
        ("AnimationId", DWORD),
    ]


class WindowCompositionAttributeData(Structure):
    _fields_ = [
        ("Attribute", DWORD),
        ("Data", POINTER(AccentPolicy)),
        ("SizeOfData", ULONG),
    ]


class MARGINS(Structure):
    _fields_ = [
        ("cxLeftWidth", c_int),
        ("cxRightWidth", c_int),
        ("cyTopHeight", c_int),
        ("cyBottomHeight", c_int),
    ]


def strtohex(_: str) -> int:
    return int(f"{_[5:7]}{_[3:5]}{_[1:3]}", base=16)


def ExtendFrameIntoClientArea(hwnd: HWND) -> None:
    margins = MARGINS(-1, -1, -1, -1)
    dwmapi.DwmExtendFrameIntoClientArea(hwnd, byref(margins))


def ApplyDarkMode(hwnd: HWND) -> None:
    dwmapi.DwmSetWindowAttribute(hwnd, 20, byref(DWORD(True)), sizeof(DWORD))

# https://github.com/marticliment/win32mica/
def ApplyMica(
    hwnd: HWND, theme: bool = False, micaalt: bool = True, extend: bool = True
) -> None:
    UNDOCUMENTED_MICA_VALUE = 0x04 if micaalt else 0x02
    DOCUMENTED_MICA_VALUE = 0x01 if micaalt else 0x04
    UNDOCUMENTED_MICA_ENTRY = 1029
    DOCUMENTED_MICA_ENTRY = 38

    flag: bool = False if getwindowsversion().build < 22523 else True
    value: int = UNDOCUMENTED_MICA_VALUE if flag else DOCUMENTED_MICA_VALUE

    entry: int = DOCUMENTED_MICA_ENTRY if flag else UNDOCUMENTED_MICA_ENTRY

    if extend:
        ExtendFrameIntoClientArea(hwnd)

    # Set the theme of the window
    if theme:
        ApplyDarkMode(hwnd)

    # Set the window's backdrop
    dwmapi.DwmSetWindowAttribute(hwnd, entry, byref(DWORD(value)), sizeof(DWORD))


def ApplyAcrylic(hwnd: HWND, theme: bool = False, extend: bool = False, hexcolor: str | None = None) -> None:
    if theme:
        ApplyDarkMode(hwnd)
    
    if extend:
        ExtendFrameIntoClientArea(hwnd)

    accentpolicy: AccentPolicy = AccentPolicy()
    data: WindowCompositionAttributeData = WindowCompositionAttributeData()
    data.Attribute = 30
    data.SizeOfData = sizeof(accentpolicy)
    data.Data = pointer(accentpolicy)

    accentpolicy.AccentState = 3

    if hexcolor:
        accentpolicy.GradientColor = DWORD(strtohex(hexcolor))

    user32.SetWindowCompositionAttribute(hwnd, pointer(data))




def SetWindowAttribute(hwnd: HWND, entry: int, hexcolor: str):
    dwmapi.DwmSetWindowAttribute(
        hwnd, entry, byref(DWORD(strtohex(hexcolor))), sizeof(DWORD)
    )


def SetWindowBorder(hwnd: HWND, type: BORDERTYPE | int) -> None:
    dwmapi.DwmSetWindowAttribute(hwnd, 33, byref(DWORD(type)), sizeof(DWORD))


SetBorderColor = partial(SetWindowAttribute, entry=34)
SetTitlebarColor = partial(SetWindowAttribute, entry=35)
SetTitleColor = partial(SetWindowAttribute, entry=36)
