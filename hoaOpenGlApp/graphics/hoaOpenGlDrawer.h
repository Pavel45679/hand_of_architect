#pragma once
#include "hoaIDrawer.h"

#include <windows.h>
#include <gl/gl.h>

class hoaPoint;

class hoaOpenGlDrawer : public hoaIDrawer {

public:
	hoaOpenGlDrawer(HDC hDC);
	~hoaOpenGlDrawer();

	void drawLine(const hoaPoint& start, const hoaPoint& end) override;
	void beginFrame() override;
	void endFrame() override;
private:
	HDC mHDC;
};
