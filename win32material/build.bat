echo off

cl /LD /DEF: .\win32material.def .\win32material.cpp

del win32material.exp win32material.obj