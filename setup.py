"""Setup for win32material"""

from distutils.core import setup

with open("README.md", "r") as file:
    long_description = file.read()

setup(
    name="win32material",
    version="1.0.6",
    description="Apply some window effects to the Win32 Applications",
    long_description=long_description,
    long_description_content_type="text/markdown",
    author="littlewhitecloud",
    url="https://github.com/littlewhitecloud/win32material",
    packages=["win32material"],
)
