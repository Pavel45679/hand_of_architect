#pragma once
#include "hoaGraphicObject.h"
class hoaIDrawer;

class hoaTestGraphicObject : public hoaGraphicObject {
public:
	hoaTestGraphicObject() = default;
	~hoaTestGraphicObject() = default;
	void draw(hoaIDrawer * drawer) override;
};
