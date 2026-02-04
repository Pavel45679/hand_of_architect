#pragma once
#include "hoaIDrawer.h"

class hoaGraphicObject {
public:
	hoaGraphicObject() = default;
	virtual ~hoaGraphicObject() = default;
	virtual void draw(hoaIDrawer * drawer) = 0;
};
