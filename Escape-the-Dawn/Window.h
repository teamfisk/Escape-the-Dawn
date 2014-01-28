#ifndef Window_h__
#define Window_h__

#include <string>

#include <Windows.h>

class Window
{
public:
	Window(HINSTANCE hInstance)
		: m_hInstance(hInstance) { }
	
	HWND GetHandle() { return m_hWnd; }
	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }

	void Create(std::string title, int width, int height);
	void Show(int nCmdShow = SW_SHOW);

	static LRESULT CALLBACK MsgRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	int m_Width;
	int m_Height;
	
	virtual LRESULT CALLBACK WndProc(UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif // Window_h__