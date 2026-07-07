#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_DESTROY) PostQuitMessage(0); // 退出消息循环
    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow
)
{
    // 注册窗口类
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"NoCapture";
    RegisterClassW(&wc);

    // 创建窗口
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

    // 设置窗口属性（透明、置顶、可穿透）
    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    // 设置窗口图标
    HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

    // 显示窗口
    ShowWindow(hwnd, SW_SHOW);

    // 设置窗口显示亲密度
    SetWindowDisplayAffinity(hwnd, WDA_MONITOR);

    // 任务栏图标
    NOTIFYICONDATAW nid = { 0 };
    nid.cbSize = sizeof(NOTIFYICONDATAW);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP;
    nid.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
    wcscpy(nid.szTip, L"防截屏中");
    Shell_NotifyIconW(NIM_ADD, &nid);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}