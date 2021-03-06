#include <windows.h>

#include "Settings.h"
#include "GDIRenderer.h"

bool gRunning		= true;
GDIRenderer renderer;

LRESULT CALLBACK MainWndProc(
	HWND hwnd,        // handle to window
	UINT uMsg,        // message identifier
	WPARAM wParam,    // first message parameter
	LPARAM lParam)    // second message parameter
{
	switch (uMsg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC dc = BeginPaint(hwnd, &paint);
			renderer.RenderToWindow(dc, WINDOW_WIDTH, WINDOW_HEIGHT);
			EndPaint(hwnd, &paint);
			break;
		}

		case WM_CLOSE:
		case WM_DESTROY:
		{
			gRunning = false;
			break;
		}

		default:
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
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
	renderer.Resize(WINDOW_WIDTH, WINDOW_HEIGHT);

	WNDCLASS wc = {};

	// Register the main window class. 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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
		hInstance,
		0
	);

	if (hWnd == NULL) return -1;
	
	/* Get infrastructures we need */
	HDC hWindowDC = GetDC(hWnd);
	
	int offsets[2] = {};

	while (gRunning)
	{
		MSG message = {};

		while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) gRunning = false;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	
		renderer.Update((void *)offsets);
		renderer.RenderToWindow(hWindowDC, WINDOW_WIDTH, WINDOW_HEIGHT);
		offsets[1]++;
	}

	return 0;
}
