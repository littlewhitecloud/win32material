// win32style.cpp - Change the window's style

#include <windows.h>
#include <dwmapi.h>

#include "win32style.h"

#pragma comment(lib, "dwmapi.lib")

void ChangeTitlebarColor(HWND hwnd, DWORD hexcolor)
{
    DwmSetWindowAttribute(hwnd, 35, &hexcolor, sizeof(int));
}

void ChangeBorderColor(HWND hwnd, DWORD hexcolor)
{
    DwmSetWindowAttribute(hwnd, 34, &hexcolor, sizeof(int));
}

void ChangeTitleColor(HWND hwnd, DWORD hexcolor)
{
    DwmSetWindowAttribute(hwnd, 36, &hexcolor, sizeof(int));
}

void SetBorderType(HWND hwnd, int type)
{
    DwmSetWindowAttribute(hwnd, 33, &type, sizeof(int));
}

void ApplyDarkMode(HWND hwnd)
{
    bool flag = true;
    DwmSetWindowAttribute(hwnd, 20, &flag, sizeof(int));
}