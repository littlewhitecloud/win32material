// win32material.cpp - Apply mica and acrylic for win32 applications
#include <Windows.h>
#include <Dwmapi.h>

#include "win32material.h"

#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "User32.lib")

static void ExtendFrameIntoClientArea(const HWND hwnd)
{   
    // Set the margins
    const MARGINS margins = {-1, -1, -1, -1};
    // Extend frame into  client area
    DwmExtendFrameIntoClientArea(hwnd, &margins);
}

static void ApplyBlurEffect(const HWND hwnd, const bool theme, const DWORD hexcolor, const bool flag)
{
    // TODO: hex color
    pfnSetWindowCompositionAttribute SetWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(GetModuleHandle("user32.dll"), "SetWindowCompositionAttribute");

    // Set the color value
    DWORD color = flag ? theme ? 1074926098 : 0 : 0;
    // Set the enable flag
    DWORD enable = flag ? theme ? 2 : 0 : 0;
    // Determine the type of the blur
    ACCENT_STATE type = flag ? ACCENT_ENABLE_ACRYLICBEHIND : ACCENT_ENABLE_BLURBEHIND;
    
    // Set the Accent Policy
    ACCENT_POLICY accentpolicy = {type, enable, color, 0};

    // Set the WindowCompositionArrtibuteData
    WINDOWCOMPOSITIONATTRIBDATA data;
    data.Attrib = WCA_ACCENT_POLICY;
    data.pvData = &accentpolicy;
    data.cbData = sizeof(accentpolicy);

    // Set the window's theme
    DwmSetWindowAttribute(hwnd, 20, &theme, sizeof(int));
    // Set the window's backdrop
    SetWindowCompositionAttribute(hwnd, &data);
}

static void ApplyMicaEffect(const HWND hwnd, const bool theme, const bool micaalt, const bool extend, const bool flag) {
    // Set the mica value
    const int value = flag ? micaalt ? 0x04 : 0x02 : micaalt ? 0x04: 0x01;
    // Set the mica entry
    const int entry = flag ? 38 : 1029;

    if (extend) // extend frame into client area
        ExtendFrameIntoClientArea(hwnd);

    // Set the window's theme
    DwmSetWindowAttribute(hwnd, 20, &theme, sizeof(int));
    // Set the window's backdrop
    DwmSetWindowAttribute(hwnd, entry, &value, sizeof(int));
}

void ApplyBlur(const HWND hwnd, const bool theme, const DWORD hexcolor)
{
    /*
    Windows 10 ~ 11
    hwnd: HWND : the window's hwnd
    theme: bool : the window's theme
    hexcolor: DWORD : the blur's hexcolor
    */
    ApplyBlurEffect(hwnd, theme, hexcolor, false);
}

void ApplyAcrylic(const HWND hwnd, const bool theme, const DWORD hexcolor)
{
    /*
    Windows 10 ~ 11
    hwnd: HWND : the window's hwnd
    theme: bool : the window's theme
    hexcolor: DWORD : the blur's hexcolor
    */
    ApplyBlurEffect(hwnd, theme, hexcolor, true);
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
    ApplyMicaEffect(hwnd, theme, micaalt, extend, true);
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
    ApplyMicaEffect(hwnd, theme, micaalt, extend, false)
}