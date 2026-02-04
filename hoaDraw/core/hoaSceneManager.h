#pragma once
#include "hoaGraphicObject.h"
#include "vector"
#include "memory"

class hoaIDrawer;

class hoaSceneManager {
public:
	hoaSceneManager(hoaIDrawer* d);

	template<typename T, typename... Args>
	void addObject(Args&&... args) {
		mObjects.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
	void drawAll();
	void clear();
private:
	std::vector<std::unique_ptr<hoaGraphicObject>> mObjects;
	hoaIDrawer* mDrawer;
};
