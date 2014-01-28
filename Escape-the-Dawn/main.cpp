#include <Windows.h>
#include <WindowsX.h>

#include "Direct3D.h"
#include "Window.h"

Direct3D* d3d;

void Update();
void Draw();

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main(int argc, char* argv[])
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	d3d = new Direct3D();

	Window wnd(hInstance);
	wnd.Create("Escape the Dawn", 1280, 720);
	d3d->Initialize(&wnd);
	wnd.Show();

	MSG msg = { 0 };
	while (true)
	{
		// Check to see if any messages are waiting in the queue
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			Update();
			Draw();
		}
	}

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}

void Update()
{

}

void Draw()
{
	d3d->DeviceContext->ClearRenderTargetView(d3d->BackBuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

	d3d->SwapChain->Present(0, 0);
}