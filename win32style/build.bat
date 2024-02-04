echo off

cl /LD /DEF: .\win32style.def .\win32style.cpp

del win32style.exp win32style.lib win32style.obj