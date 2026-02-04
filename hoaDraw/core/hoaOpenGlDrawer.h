#pragma once
#include "hoaIDrawer.h"

#include <windows.h>
#include <gl/gl.h>

class hoaPoint;

class hoaOpenGlDrawer : public hoaIDrawer {

public:
	hoaOpenGlDrawer(HDC hdc, int w, int h);
	~hoaOpenGlDrawer();

	void drawLine(const hoaPoint& start, const hoaPoint& end) override;
	void beginFrame();
	void endFrame();

private:
	HDC hDC;
	int width, height;

	bool setupPixelFormat();
	void setupOrtho2D();
};
