#ifndef Direct3D_h__
#define Direct3D_h__

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include "Window.h"

class Direct3D
{
public:
	Direct3D() { }
	~Direct3D();

	IDXGISwapChain* SwapChain;
	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;
	ID3D11RenderTargetView* BackBuffer;

	void Initialize(Window* window);
	void Resize(int width, int height);

private:
	Window* m_Window;
};

#endif // Direct3D_h__