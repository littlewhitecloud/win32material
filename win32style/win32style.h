// win32style.h - Define the functions

#pragma once

#ifdef WIN32STYLE_EXPORTS
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif

extern "C" {
    DLLEXPORT void ChangeTitlebarColor(HWND hwnd, DWORD color);
    DLLEXPORT void ChangeBorderColor(HWND hwnd, DWORD hexcolor);
    DLLEXPORT void ChangeTitleColor(HWND hwnd, DWORD hexcolor);
    DLLEXPORT void SetBorderType(HWND hwnd, int type);
    DLLEXPORT void ApplyDarkMode(HWND hwnd);
}