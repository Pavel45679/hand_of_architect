#include "graphics/hoaOpenGlWindow.h"
#include "hoaContext.h"
#include "hoaDataBase.h"
#include "hoaSceneManager.h"
#include "graphics/hoaTestGraphicObject.h"
#include "graphics/hoaOpenGlDrawer.h"
#include "hoaIDrawer.h"

void initContext(hoaContext& context, HDC hDC) {
	context.mDrawer = std::make_unique<hoaOpenGlDrawer>(hDC);
	context.mScene = std::make_unique<hoaSceneManager>(*context.mDrawer);
	context.mDataBase = std::make_unique<hoaDataBase>();

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	hoaOpenGlWindow window(hInstance);

	if (!window.create()) {
		MessageBoxW(NULL, L"Не удалось создать окно", L"Ошибка", MB_ICONERROR);
		return 1;
	}

	hoaContext context;
	initContext(context, window.getHDC());

	context.mScene->addObject<hoaTestGraphicObject>();

	window.run(context);

	return 0;
}
