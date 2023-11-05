// renderer.h - class for initializing dx12 and basic rendering
#pragma once

#include "helpers.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;

class Renderer {
public:
    Renderer(UINT width, UINT height);

    // Initialize all resources
    void OnInit(HWND hwnd);
    // Update resources if needed
    void OnUpdate();
    // Main render function
    void OnRender();
    // Terminate all resources
    void OnDestroy();

    // Get width of window
    UINT GetWidth() const { return width; };
    // Get height of window
    UINT GetHeight() const { return height; };
private:
    // TODO: remove hwnd and replace it with reference to application?
    HWND hwnd;
    UINT width;
    UINT height;
    float aspectRatio;

    static const UINT FrameCount = 2;

    struct Vertex
    {
        XMFLOAT3 position;
        XMFLOAT4 color;
    };

    // Pipeline objects.
    CD3DX12_VIEWPORT viewport;
    CD3DX12_RECT scissorRect;

    ComPtr<IDXGISwapChain3> pSwapChain;
    ComPtr<ID3D12Device> pDevice;
    ComPtr<ID3D12Resource> pRenderTargets[FrameCount];
    ComPtr<ID3D12CommandAllocator> pCommandAllocator;
    ComPtr<ID3D12CommandQueue> pCommandQueue;
    ComPtr<ID3D12RootSignature> pRootSignature;
    ComPtr<ID3D12DescriptorHeap> pRtvHeap;
    ComPtr<ID3D12PipelineState> pPipelineState;
    ComPtr<ID3D12GraphicsCommandList> pCommandList;
    UINT rtvDescriptorSize;

    // App resources.
    ComPtr<ID3D12Resource> vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

    // Synchronization objects.
    UINT frameIndex;
    HANDLE fenceEvent;
    ComPtr<ID3D12Fence> fence;
    UINT64 fenceValue;

    // Load the rendering pipeline dependencies
    void LoadPipeline();
    void LoadAssets();
    void PopulateCommandList();
    void WaitForPreviousFrame();
};
