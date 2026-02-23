#include "hoaOpenGlWindow.h"
#include <windows.h>
#include <GL/gl.h>
#include "hoaContext.h"
#include "hoaSceneManager.h"

LRESULT CALLBACK hoaOpenGlWindow::WindowProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {
	hoaOpenGlWindow* window = nullptr;

	if (message == WM_NCCREATE) {
		CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
		window = (hoaOpenGlWindow*)cs->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
		window->hWnd = hWnd;
	}
	else {
		window = (hoaOpenGlWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if (window) {
		return window->handleMessage(message, wParam, lParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

hoaOpenGlWindow::hoaOpenGlWindow(HINSTANCE hInst) :
	hInstance(hInst), hWnd(NULL), hDC(NULL), hRC(NULL) {
}

hoaOpenGlWindow::~hoaOpenGlWindow() {
	if (hRC) {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRC);
		hRC = NULL;
	}

	if (hDC) {
		ReleaseDC(hWnd, hDC);
		hDC = NULL;
	}
}

bool hoaOpenGlWindow::create() {
	WNDCLASSW wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance ? hInstance : GetModuleHandleW(NULL);
	wc.lpszClassName = L"OpenGLWindowClass";
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;

	if (!RegisterClassW(&wc)) {
		DWORD err = GetLastError();
		return false;
	}

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	hWnd = CreateWindowW(
		L"OpenGLWindowClass",
		L"Hand of Arhitecter",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowWidth, windowHeight,
		NULL,
		NULL,
		wc.hInstance,
		this
	);

	if (!hWnd) {
		DWORD err = GetLastError();
		return false;
	}

	hDC = GetDC(hWnd);
	if (!hDC) {
		DestroyWindow(hWnd);
		hWnd = NULL;
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0, 0,
		0, 0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int pixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (!pixelFormat) {
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		hWnd = NULL;
		hDC = NULL;
		return false;
	}

	if (!SetPixelFormat(hDC, pixelFormat, &pfd)) {
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		hWnd = NULL;
		hDC = NULL;
		return false;
	}

	hRC = wglCreateContext(hDC);
	if (!hRC) {
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		hWnd = NULL;
		hDC = NULL;
		return false;
	}

	if (!wglMakeCurrent(hDC, hRC)) {
		wglDeleteContext(hRC);
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		hWnd = NULL;
		hDC = NULL;
		hRC = NULL;
		return false;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 800, 600);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return true;
}

void hoaOpenGlWindow::run(hoaContext& context) {
	MSG msg = {};
	DWORD lastTick = GetTickCount();

	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			DWORD currentTick = GetTickCount();
			float deltaTime = (currentTick - lastTick) / 1000.0f;
			lastTick = currentTick;

			if (deltaTime > 0.1f) deltaTime = 0.1f;

			if (context.mScene) {
				context.mScene->drawAll();
			}
		}
	}
}

LRESULT hoaOpenGlWindow::handleMessage(UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;

	case WM_SIZE:
		if (/*mDrawer &&*/ wParam != SIZE_MINIMIZED) {
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			glViewport(0, 0, width, height);

			//mDrawer->setViewportSize(width, height);

			InvalidateRect(hWnd, NULL, FALSE);
		}
		return 0;

	case WM_PAINT: {
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);

		/*if (mScene) {
			mScene->drawAll();
		}*/

		EndPaint(hWnd, &ps);
		return 0;
	}

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
		}
		return 0;

	case WM_ERASEBKGND:
		return 1;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
