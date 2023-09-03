// win32material.cpp - Apply mica and acrylic for win32 applications
#include <Windows.h>
#include <Dwmapi.h>

#include "win32material.h"

#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "User32.lib")

static void ExtendFrameIntoClientArea(const HWND hwnd)
{
    const MARGINS margins = {-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea(hwnd, &margins);
}

static void ApplyBlurBehind(const HWND hwnd, const bool theme, const DWORD hexcolor, const bool type)
{ // Windows 10 & 11
    // TODO: hex color
    pfnSetWindowCompositionAttribute SetWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(GetModuleHandle("user32.dll"), "SetWindowCompositionAttribute");

    ACCENT_POLICY accentpolicy = { type ? ACCENT_ENABLE_ACRYLICBEHIND : ACCENT_ENABLE_BLURBEHIND, type ? 2 : 0, type ? theme ? 1074926098: 0 : 0, 0};

    WINDOWCOMPOSITIONATTRIBDATA data;
    data.Attrib = WCA_ACCENT_POLICY;
    data.pvData = &accentpolicy;
    data.cbData = sizeof(accentpolicy);

    DwmSetWindowAttribute(hwnd, 20, &theme, sizeof(int));
    SetWindowCompositionAttribute(hwnd, &data);
}

void ApplyBlur(const HWND hwnd, const bool theme, const DWORD hexcolor)
{
    /*
    Windows 10 & 11
    hwnd: HWND : the window's hwnd
    theme: bool : the window's theme
    hexcolor: DWORD : the blur's hexcolor
    */
    ApplyBlurBehind(hwnd, theme, hexcolor, false);
}

void ApplyAcrylic(const HWND hwnd, const bool theme, const DWORD hexcolor)
{
    /*
    Windows 10 & 11
    hwnd: HWND : the window's hwnd
    theme: bool : the window's theme
    hexcolor: DWORD : the blur's hexcolor
    */
    ApplyBlurBehind(hwnd, theme, hexcolor, true);
}

void ApplyDocumentMica(const HWND hwnd, const bool theme, const bool micaalt, const bool extend)
{
    /*
        Windows 11 23523+
        hwnd: HWND : the window's hwnd
        theme: bool : the window's theme
        micaalt: bool : determine which type of mica
        extend: bool : extend to the client area
    */
    const int value = micaalt ? 0x04 : 0x02;

    if (extend)
        ExtendFrameIntoClientArea(hwnd);

    // Set the window's theme
    DwmSetWindowAttribute(hwnd, 20, &theme, sizeof(int));
    // Set the window's backdrop
	DwmSetWindowAttribute(hwnd, 38, &value, sizeof(int));
}

void ApplyUndocumentMica(const HWND hwnd, const bool theme, const bool micaalt, const bool extend)
{
    /*
    Windows 11 23523-
    hwnd: HWND : the window's hwnd
    theme: bool : the window's theme
    micaalt: bool : determine which type of mica
    extend: bool : extend to the client area
    */
    const int value = micaalt ? 0x04 : 0x01;

    if (extend)
        ExtendFrameIntoClientArea(hwnd);

    // Set the window's theme
	DwmSetWindowAttribute(hwnd, 20, &theme, sizeof(int));
    // Set the window's backdrop
    DwmSetWindowAttribute(hwnd, 1029, &value, sizeof(int));
}