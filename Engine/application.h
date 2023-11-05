// application.h - class for initializing all program work
#pragma once

#include "renderer.h"

class Renderer;

class Application {
public:
    // Main function
    static int Run(Renderer* pRenerer, HINSTANCE hInstance, INT nCmdShow);
protected:
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
    static void InitWindow(Renderer* renderer, HINSTANCE hInstance, INT nCmdShow);

    static HWND hwnd;
};
