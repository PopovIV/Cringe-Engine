#include "stdafx.h"
#include "resource.h"
#include "application.h"

HWND Application::hwnd = nullptr;

// Main function
int Application::Run(Renderer* pRenderer, HINSTANCE hInstance, INT nCmdShow)
{
    // Init window
    InitWindow(pRenderer, hInstance, nCmdShow);

    // Init renderer
    pRenderer->OnInit(hwnd);

    ShowWindow(hwnd, nCmdShow);

    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Delete all resources
    pRenderer->OnDestroy();

    return static_cast<int>(msg.wParam);
}


// Register class and create window
void Application::InitWindow(Renderer* pRenderer, HINSTANCE hInstance, INT nCmdShow)
{
    const WCHAR* windowClassName = L"WindowClass";
    const WCHAR* WindowTitle = L"Cringe Engine";
    HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));

    // Register window class
    WNDCLASSEX windowClass = { 0 };
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = hIcon;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.hbrBackground = nullptr;
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = windowClassName;
    //windowClass.hIconSm = 0;
    RegisterClassEx(&windowClass);

    RECT windowRect = { 0, 0, static_cast<LONG>(pRenderer->GetWidth()), static_cast<LONG>(pRenderer->GetHeight()) };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    // Create window
    hwnd = CreateWindow(
        windowClassName,
        WindowTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,
        nullptr,
        hInstance,
        pRenderer);

}



// Called every time the application receives a message
LRESULT CALLBACK Application::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Renderer* pRenderer = reinterpret_cast<Renderer*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message) {
    case WM_CREATE:
    {
        LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
        break;
    }
    case WM_PAINT:
        if (pRenderer) {
            pRenderer->OnUpdate();
            pRenderer->OnRender();
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
