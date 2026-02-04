#include "hoaSceneManager.h"
#include "hoaIDrawer.h"

hoaSceneManager::hoaSceneManager(hoaIDrawer* d) : mDrawer(d) {
}

void hoaSceneManager::drawAll() {
	mDrawer->beginFrame();
	for (const auto& obj : mObjects) {
		obj->draw(mDrawer);
	}
	mDrawer->endFrame();
}

void hoaSceneManager::clear() {
	mObjects.clear();
}
