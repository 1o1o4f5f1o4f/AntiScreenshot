#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_DESTROY) PostQuitMessage(0);
    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow
)
{
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"NoCapture";
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT,
        L"NoCapture",
        NULL,
        WS_POPUP,
        0, 0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, hInstance, NULL
    );

    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

    ShowWindow(hwnd, SW_SHOW);
    SetWindowDisplayAffinity(hwnd, WDA_MONITOR);

    NOTIFYICONDATAW nid = { 0 };
    nid.cbSize = sizeof(NOTIFYICONDATAW);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP;
    nid.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
    wcscpy(nid.szTip, L"防截屏中");
    Shell_NotifyIconW(NIM_ADD, &nid);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}