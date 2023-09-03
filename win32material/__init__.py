"""Load functions from win32mica.py"""
from platform import platform
if not platform().startswith("Windows-10"):
    raise OSError("At least you need to use Windows 10 to run the program")

from .win32material import ApplyAcrylic, ApplyMica, ApplyBlur