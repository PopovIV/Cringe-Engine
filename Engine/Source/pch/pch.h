#pragma once

// includes
#include "../../resource.h"
#include "windows.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl\client.h>

#pragma comment (lib, "d3d12.lib")
#pragma comment (lib, "dxgi.lib")

// defines
#define MAX_NAME_STRING 256
#define hInstance() GetModuleHandle(NULL)

#define SAFE_RELEASE(p) \
if (p != NULL) { \
    p->Release(); \
    p = NULL; \
}

#define SAFE_DELETE(p) \
if(p != NULL) { \
    delete (p); \
    p = NULL; \
} \
