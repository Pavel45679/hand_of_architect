#pragma once
#include <windows.h>
#include <gl/gl.h>

class hoaOpenGlDrawer;
class hoaSceneManager;
class hoaContext;

class hoaOpenGlWindow {

public:
	hoaOpenGlWindow(HINSTANCE hInst);
	~hoaOpenGlWindow();
	bool create();
	void run(hoaContext& context);
	HDC getHDC() {
		return hDC;
	}
private:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT handleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	HINSTANCE hInstance;
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
};
