// win32style.cpp - Apply mica and acrylic for win32 applications

#undef UNICODE
#undef _UNICODE

#include <windows.h>
#include <dwmapi.h>

#include "win32style.h"

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "user32.lib")

static void ExtendFrameIntoClientArea(HWND hwnd)
{
    // Set the margins
    const MARGINS margins = {-1};
    // Extend frame into  client area
    DwmExtendFrameIntoClientArea(hwnd, &margins);
}

static void ApplyMicaEffect(HWND hwnd, bool theme, bool micaalt, bool extend, bool flag = true)
{
    // Set the mica value
    const int value = flag ? micaalt ? 0x04 : 0x02 : micaalt ? 0x04
                                                            : 0x01;
    // Set the mica entry
    const int entry = flag ? 38 : 1029;

    if (extend) // extend frame into client area
        ExtendFrameIntoClientArea(hwnd);

    // Set the window's theme
    DwmSetWindowAttribute(hwnd, 20, &theme, sizeof(int));
    // Set the window's backdrop
    DwmSetWindowAttribute(hwnd, entry, &value, sizeof(int));
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
    ApplyMicaEffect(hwnd, theme, micaalt, extend);
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

void ApplyAcrylic(HWND hwnd, bool extend = false, DWORD hexcolor = 0)
{
    pfnSetWindowCompositionAttribute SetWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(GetModuleHandle("user32.dll"), "SetWindowCompositionAttribute");
    DWORD gradientcolor = DWORD(0x50F5F5F5);
    if (hexcolor)
        gradientcolor = hexcolor;

    ApplyDarkMode(hwnd);

    ACCENT_POLICY accentpolicy = {};

    accentpolicy.AccentState = 3;
    accentpolicy.GradientColor = gradientcolor;
    // Set the WindowCompositionArrtibuteData
    WINDOWCOMPOSITIONATTRIBDATA data;
    data.Attrib = 30;
    data.pvData = &accentpolicy;
    data.cbData = sizeof(accentpolicy);

    // Set the window's backdrop
    SetWindowCompositionAttribute(hwnd, &data);
    if (extend)
        ExtendFrameIntoClientArea(hwnd);
}

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