#include "hoaOpenGlWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	hoaOpenGlWindow window(hInstance);

	if (!window.create(L"Чистое OpenGL - Система рисования", 800, 600)) {
		MessageBoxW(NULL, L"Не удалось создать окно", L"Ошибка", MB_ICONERROR);
		return 1;
	}

	window.run();

	return 0;
}
