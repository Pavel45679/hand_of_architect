#include "hoaOpenGlDrawer.h"

hoaOpenGlDrawer::hoaOpenGlDrawer(HDC hDC) : mHDC(hDC){
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2.0f);
}

hoaOpenGlDrawer::~hoaOpenGlDrawer() = default;

void hoaOpenGlDrawer::drawLine(const hoaPoint& start, const hoaPoint& end){
	glColor3f(0, 255, 0);
	glBegin(GL_LINES);
	glVertex3f(static_cast<GLfloat>(start.x), static_cast<GLfloat>(start.y), static_cast<GLfloat>(start.z));
	glVertex3f(static_cast<GLfloat>(end.x), static_cast<GLfloat>(end.y), static_cast<GLfloat>(end.z));
	glEnd();
}

void hoaOpenGlDrawer::beginFrame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void hoaOpenGlDrawer::endFrame() {
	SwapBuffers(mHDC);
}
