"""Load functions"""
from platform import platform

if not platform().startswith("Windows-10") and not platform().startswith("Windows-11"):
    raise OSError("To use this package, you need to use Windows 10 or above")

from .win32material import (
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
