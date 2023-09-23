/*
     ______ .______       __  .__   __.   _______  _______     _______ .__   __.   _______  __  .__   __.  _______ 
    /      ||   _  \     |  | |  \ |  |  /  _____||   ____|   |   ____||  \ |  |  /  _____||  | |  \ |  | |   ____|
   |  ,----'|  |_)  |    |  | |   \|  | |  |  __  |  |__      |  |__   |   \|  | |  |  __  |  | |   \|  | |  |__   
   |  |     |      /     |  | |  . `  | |  | |_ | |   __|     |   __|  |  . `  | |  | |_ | |  | |  . `  | |   __|  
   |  `----.|  |\  \----.|  | |  |\   | |  |__| | |  |____    |  |____ |  |\   | |  |__| | |  | |  |\   | |  |____ 
    \______|| _| `._____||__| |__| \__|  \______| |_______|   |_______||__| \__|  \______| |__| |__| \__| |_______|
                                                                                                                  
*/

//--------------------------------------------------------------------------------------
//  WinMain.cpp - entry point of programm
//--------------------------------------------------------------------------------------

#include "pch/pch.h"

// Global Variables
HINSTANCE               g_hInst = nullptr;
UINT                    WindowWidth = 1280;
UINT                    WindowHeight = 720;
WCHAR                   WindowClass[MAX_NAME_STRING];
WCHAR                   WindowTitle[MAX_NAME_STRING];

// Forward declarations
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (FAILED(InitWindow(hInstance, nCmdShow))) {
        MessageBox(0, L"Failed to Create Window!.", 0, 0);
        return FALSE;
    }

    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}


// Register class and create window
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    wcscpy_s(WindowClass, TEXT("WindowClass"));
    wcscpy_s(WindowTitle, TEXT("Cringe Engine"));

    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = 0;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = WindowClass;
    wcex.hIconSm = 0;
    if (!RegisterClassEx(&wcex)) {
        return E_FAIL;
    }

    // Create window
    g_hInst = hInstance;
    HWND hWnd = CreateWindow(WindowClass, WindowTitle,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr,
        nullptr, hInstance, nullptr);
    if (!hWnd) {
        return E_FAIL;
    }

    ShowWindow(hWnd, nCmdShow);

    return TRUE;
}



// Called every time the application receives a message
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
      case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
      case WM_DESTROY:
        PostQuitMessage(0);
        break;
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
