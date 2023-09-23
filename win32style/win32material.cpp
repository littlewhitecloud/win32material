// win32material.cpp - Apply mica and acrylic for win32 applications

#undef UNICODE
#undef _UNICODE

#include <windows.h>
#include <dwmapi.h>

#include "win32material.h"

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "user32.lib")

static void ExtendFrameIntoClientArea(HWND hwnd)
{   
    // Set the margins
    const MARGINS margins = {-1, -1, -1, -1};
    // Extend frame into  client area
    DwmExtendFrameIntoClientArea(hwnd, &margins);
}

static void ApplyBlurEffect(HWND hwnd, bool theme, DWORD hexcolor, bool flag)
{
    // TODO: hex color
    pfnSetWindowCompositionAttribute SetWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(GetModuleHandle("user32.dll"), "SetWindowCompositionAttribute");

    // Set the color value
    const DWORD color = flag ? theme ? 1074926098 : 0 : 0;
    // Set the enable flag
    const DWORD enable = flag ? theme ? 2 : 0 : 0;
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

static void ApplyMicaEffect(HWND hwnd, bool theme, bool micaalt, bool extend, bool flag) {
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

void ApplyBlur(HWND hwnd, bool theme, DWORD hexcolor)
{
    /*
    Windows 10 ~ 11
    hwnd: HWND : the window's hwnd
    theme: bool : the window's theme
    hexcolor: DWORD : the blur's hexcolor
    */
    ApplyBlurEffect(hwnd, theme, hexcolor, false);
}

void ApplyAcrylic(HWND hwnd, bool theme, DWORD hexcolor)
{
    /*
    Windows 10 ~ 11
    hwnd: HWND : the window's hwnd
    theme: bool : the window's theme
    hexcolor: DWORD : the blur's hexcolor
    */
    ApplyBlurEffect(hwnd, theme, hexcolor, true);
}

void ApplyDocumentMica(HWND hwnd, bool theme, bool micaalt, bool extend)
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

void ApplyUndocumentMica(HWND hwnd, bool theme, bool micaalt, bool extend)
{
    /*
    Windows 11 23523-
    hwnd: HWND : the window's hwnd
    theme: bool : the window's theme
    micaalt: bool : determine which type of mica
    extend: bool : extend to the client area
    */
    ApplyMicaEffect(hwnd, theme, micaalt, extend, false);
}