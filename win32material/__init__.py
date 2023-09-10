"""Load functions from win32material.py"""
from platform import platform

if not platform().startswith("Windows-10"):
    raise OSError("To use this package, you need to use Windows version >= 10")

from .win32material import ApplyAcrylic, ApplyBlur, ApplyMica, ChangeTitlebarColor, ChangeBorderColor, ChangeTitleColor, SetBorderType

from .win32material import MICAMODE, MICATHEME, BORDERTYPE