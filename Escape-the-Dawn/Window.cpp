#include "Window.h"

LRESULT CALLBACK Window::MsgRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CREATE)
		SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<long>(LPCREATESTRUCT(lParam)->lpCreateParams));

	Window* wnd = reinterpret_cast<Window*>(GetWindowLong(hWnd, GWL_USERDATA));

	if (wnd)
		return wnd->WndProc(msg, wParam, lParam);
	else
		return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Window::Create(std::string title, int width, int height)
{
	m_Width = width;
	m_Height = height;

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Window::MsgRouter;
	wc.hInstance = m_hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	m_hWnd = CreateWindowEx(
		NULL,
		"WindowClass1",
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		m_hInstance,
		reinterpret_cast<void*>(this));
}

void Window::Show(int nCmdShow /*= SW_SHOW*/)
{
	ShowWindow(m_hWnd, nCmdShow);
}

LRESULT CALLBACK Window::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		OutputDebugString("WM_CREATE\n");
	case WM_CLOSE:
		DestroyWindow(m_hWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(m_hWnd, msg, wParam, lParam);
	}
}