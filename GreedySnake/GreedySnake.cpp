#include <windows.h>

#include "Settings.h"

LRESULT CALLBACK MainWndProc(
	HWND hwnd,        // handle to window
	UINT uMsg,        // message identifier
	WPARAM wParam,    // first message parameter
	LPARAM lParam)    // second message parameter
{

	switch (uMsg)
	{
	case WM_CREATE:
		// Initialize the window. 
		return 0;

	case WM_PAINT:
		// Paint the window's client area. 
		return 0;

	case WM_SIZE:
		// Set the size and position of the window. 
		return 0;

	case WM_DESTROY:
		// Clean up window-specific data objects. 
		return 0;

		// 
		// Process other messages. 
		// 

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow
)
{
	WNDCLASS wc = {};

	// Register the main window class. 
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"MainWindowClass";

	if (!RegisterClass(&wc)) return -1;

	HWND hWnd = CreateWindowEx(
		0,
		wc.lpszClassName,
		L"Greedy Snake by HW",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		WINDOW_X,
		WINDOW_Y,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0,
		0,
		wc.hInstance,
		0
	);

	if (hWnd == NULL) return -1;
	
	for (;;)
	{
		MSG message = {};
		if (GetMessage(&message, 0, 0, 0))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	return 0;
}
