#pragma once
#include <windows.h>
#include <gl/gl.h>

class hoaOpenGlDrawer;
class hoaSceneManager;

class hoaOpenGlWindow {

public:
	hoaOpenGlWindow(HINSTANCE hInst);
	~hoaOpenGlWindow();
	bool create(const wchar_t* title, int width, int height);
	void run();

private:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT handleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void createScene();
	HINSTANCE hInstance;
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
	hoaOpenGlDrawer* mDrawer;
	hoaSceneManager* mScene;
};
