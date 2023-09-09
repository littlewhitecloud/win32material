"""Setup for win32material"""
from distutils.core import setup

with open("README.md", "r") as file:
    long_description = file.read()

setup(
    name="win32material",
    version="1.0.0",
    description="Apply some window effects to the Win32 Applications",
    long_description=long_description,
    long_description_content_type="text/markdown",
    author="littlewhitecloud",
    exclude_package_data={
        "": ["win32material.def"],
        "": ["win32material.h"],
        "": ["win32material.cpp"],
    },
    url="https://github.com/littlewhitecloud/win32material",
    include_package_data=True,
    packages=["win32material"],
)
