"""Setup for win32style"""
from distutils.core import setup

with open("README.md", "r") as file:
    long_description = file.read()

setup(
    name="win32style",
    version="1.0.4",
    description="Apply some window effects to the Win32 Applications",
    long_description=long_description,
    long_description_content_type="text/markdown",
    author="littlewhitecloud",
    exclude_package_data={
        "": ["win32style.def"],
        "": ["win32style.h"],
        "": ["win32style.cpp"],
    },
    package_data={
        "": ["*.dll"],
    },
    url="https://github.com/littlewhitecloud/win32style",
    packages=["win32style"],
)
