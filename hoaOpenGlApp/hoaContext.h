#pragma once
#include <memory>

class hoaSceneManager;
class hoaDataBase;
class hoaIDrawer;
class hoaWrapperManager;

class hoaContext {
public:
	std::unique_ptr<hoaSceneManager> mScene;
	std::unique_ptr<hoaDataBase> mDataBase;
	std::unique_ptr<hoaIDrawer> mDrawer;
	std::unique_ptr<hoaWrapperManager> mWrapperManager;
};
