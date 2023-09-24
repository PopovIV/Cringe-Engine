#include "renderer.h"

// Initialize all resources
HRESULT Renderer::Init(HINSTANCE hInstance, HWND hWnd)
{
    HRESULT hr;

#ifdef _DEBUG
    // Enable the D3D12 debug layer
    {
        ComPtr<ID3D12Debug> pDebugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController)))) {
            pDebugController->EnableDebugLayer();
        }
    }
#endif

    // Create a DirectX device
    while (true) {
        if (SUCCEEDED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&pDevice))))
            break;
        if (SUCCEEDED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&pDevice))))
            break;
        if (SUCCEEDED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_1, IID_PPV_ARGS(&pDevice))))
            break;
        if (SUCCEEDED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&pDevice))))
            break;
        return E_FAIL;
    }


    // Create a DirectX factory
    ComPtr<IDXGIFactory4> pFactory4;
    hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory4));

    // Describe and create the command queue
    if (SUCCEEDED(hr)) {
        D3D12_COMMAND_QUEUE_DESC queueDesc = {};
        pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pCommandQueue));
    }

    // Describe and create the swap chain
    if (SUCCEEDED(hr)) {
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChainDesc.BufferCount = 2;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.OutputWindow = hWnd;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.Windowed = TRUE;

        hr = pFactory4->CreateSwapChain(pCommandQueue.Get(), &swapChainDesc, &pSwapChain);
    }

    // Create descriptor heaps
    // Describe and create a render target view(RTV) descriptor heap.
    if (SUCCEEDED(hr)) {
        D3D12_DESCRIPTOR_HEAP_DESC hDesc = {};
        hDesc.NumDescriptors = 2;
        hDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        hr = pDevice->CreateDescriptorHeap(&hDesc, IID_PPV_ARGS(&pDescHeap));
    }

    if (SUCCEEDED(hr)) {
        ID3D12Resource* resource;
        pSwapChain.As(&pSwapChain3);
        pSwapChain3->GetBuffer(0, IID_PPV_ARGS(&resource));
        pDevice->CreateRenderTargetView(resource, nullptr, pDescHeap->GetCPUDescriptorHandleForHeapStart());
        SAFE_RELEASE(resource);
    }

    ComPtr<ID3D12CommandAllocator> pCommandAllocator;
    // Create the command allocator
    if (SUCCEEDED(hr)) {
        hr = pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&pCommandAllocator));
    }

    // Create the command list
    if (SUCCEEDED(hr)) {
        hr = pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
            pCommandAllocator.Get(), nullptr, IID_PPV_ARGS(&pCommandList));
    }

    pFactory4.ReleaseAndGetAddressOf();
    pCommandAllocator.ReleaseAndGetAddressOf();

    return hr;
}


// Terminate all resources
void Renderer::Term()
{
    pDevice.ReleaseAndGetAddressOf();
    pCommandQueue.ReleaseAndGetAddressOf();
    pCommandList.ReleaseAndGetAddressOf();
    pDescHeap.ReleaseAndGetAddressOf();
    pSwapChain.ReleaseAndGetAddressOf();
    pSwapChain3.ReleaseAndGetAddressOf();
}

// Main render function
void Renderer::Render()
{
    const float Color[] = { 0.4f, 0.6f, 0.9f, 1.0f };
    pCommandList->ClearRenderTargetView(pDescHeap->GetCPUDescriptorHandleForHeapStart(), Color, 0, nullptr);
    pCommandList->Close();

    ID3D12CommandList* pCommandLists[] = { pCommandList.Get() };
    pCommandQueue->ExecuteCommandLists(_countof(pCommandLists), pCommandLists);
    pSwapChain3->Present(1, 0);
}
