"""Load functions from win32material.py"""
from platform import platform

if not platform().startswith("Windows-10"):
    raise OSError("To use this package, you need to use Windows version >= 10")

from .win32style import (
    BORDERTYPE,
    MICAMODE,
    MICATHEME,
    ApplyAcrylic,
    ApplyDarkMode,
    ApplyMica,
    ChangeBorderColor,
    ChangeTitlebarColor,
    ChangeTitleColor,
    SetBorderType,
)
