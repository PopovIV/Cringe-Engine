// Renderer.h - class for initializing dx12 and basic rendering
#pragma once

#include "../pch/pch.h"

using namespace Microsoft::WRL;

class Renderer {
public:
    // Initialize all resources
    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    // Terminate all resources
    void Term();

    // Main render function
    void Render();
private:
    ComPtr<ID3D12Device> pDevice;
    ComPtr<ID3D12CommandQueue> pCommandQueue;
    ComPtr<ID3D12GraphicsCommandList> pCommandList;
    ComPtr<ID3D12DescriptorHeap> pDescHeap;

    ComPtr<IDXGISwapChain> pSwapChain;
    ComPtr<IDXGISwapChain3> pSwapChain3;
};