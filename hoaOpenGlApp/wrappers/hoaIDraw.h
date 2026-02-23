#pragma once
#include "wrappers/hoaWrapper.h"

class hoaIDrawer;

class hoaIDraw : public hoaWrapper {
public:
	void draw(hoaIDrawer* drawer) = 0;
};
