#include "Direct3D.h"

void Direct3D::Initialize(Window* window)
{
	m_Window = window;

	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = window->GetHandle();
	scd.SampleDesc.Count = 4;
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&SwapChain,
		&Device,
		NULL,
		&DeviceContext);

	// Set the back buffer render target
	ID3D11Texture2D* pBackBuffer;
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	Device->CreateRenderTargetView(pBackBuffer, NULL, &BackBuffer);
	pBackBuffer->Release();
	DeviceContext->OMSetRenderTargets(1, &BackBuffer, NULL);

	// Set the viewport
	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = window->GetWidth();
	viewport.Height = window->GetHeight();
	DeviceContext->RSSetViewports(1, &viewport);
}

void Direct3D::Resize(int width, int height)
{
	DeviceContext->OMSetRenderTargets(0, 0, 0);
	BackBuffer->Release();

	HRESULT hr; // TODO: Error handling
	// Preserve the existing buffer count and format.
	hr = SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

	ID3D11Texture2D* pBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
	hr = Device->CreateRenderTargetView(pBuffer, NULL, &BackBuffer);
	pBuffer->Release();
	DeviceContext->OMSetRenderTargets(1, &BackBuffer, NULL);

	// Set the viewport
	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	DeviceContext->RSSetViewports(1, &viewport);
}

Direct3D::~Direct3D()
{
	SwapChain->Release();
	BackBuffer->Release();
	Device->Release();
	DeviceContext->Release();
}