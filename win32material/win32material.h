// win32material.h - Define the functions and structs

#pragma once

#ifdef WIN32MATERIAL_EXPORTS
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif

typedef struct _WINDOWCOMPOSITIONATTRIBDATA
{
    DWORD Attrib;
    PVOID pvData;
    SIZE_T cbData;
} WINDOWCOMPOSITIONATTRIBDATA;

typedef struct _ACCENT_POLICY
{
    DWORD AccentState;
    DWORD AccentFlags;
    DWORD GradientColor;
    DWORD AnimationId;
} ACCENT_POLICY;

WINUSERAPI BOOL WINAPI SetWindowCompositionAttribute(
    _In_ HWND hWnd,
    _Inout_ WINDOWCOMPOSITIONATTRIBDATA *pAttrData);

typedef BOOL(WINAPI *pfnSetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBDATA *);

extern "C"
{
    DLLEXPORT void ApplyAcrylic(HWND hwnd, DWORD hexcolor);
    DLLEXPORT void ApplyDocumentMica(HWND hwnd, bool theme, bool micaalt, bool extend);
    DLLEXPORT void ApplyUndocumentMica(HWND hwnd, bool theme, bool micaalt, bool extend);

    DLLEXPORT void ChangeTitlebarColor(HWND hwnd, DWORD color);
    DLLEXPORT void ChangeBorderColor(HWND hwnd, DWORD hexcolor);
    DLLEXPORT void ChangeTitleColor(HWND hwnd, DWORD hexcolor);
    DLLEXPORT void SetBorderType(HWND hwnd, int type);
    DLLEXPORT void ApplyDarkMode(HWND hwnd);
}