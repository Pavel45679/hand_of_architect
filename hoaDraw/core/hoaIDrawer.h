#pragma once
#include "hoaPoint.h"

class hoaIDrawer {
public:
	virtual ~hoaIDrawer() = default;
	virtual void drawLine(const hoaPoint& start, const hoaPoint& end) = 0;
	virtual void beginFrame() = 0;
	virtual void endFrame() = 0;
};
