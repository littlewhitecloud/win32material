echo off

cl /LD /DEF: .\win32style.def .\win32style.cpp
cl /LD /DEF: .\win32material.def .\win32material.cpp

del win32material.exp win32material.lib win32material.obj
del win32style.exp win32style.lib win32style.obj