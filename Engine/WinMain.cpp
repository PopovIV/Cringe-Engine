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

#include "stdafx.h"
#include "application.h"

// Global variables
UINT                    WindowWidth = 1280;
UINT                    WindowHeight = 720;


// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
_Use_decl_annotations_
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
    // TODO: initialize with .ini file?
    Renderer renderer(WindowWidth, WindowHeight);
    return Application::Run(&renderer, hInstance, nCmdShow);
}
