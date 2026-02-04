#include "hoaOpenGlDrawer.h"

hoaOpenGlDrawer::hoaOpenGlDrawer(HDC hdc, int w, int h) : hDC(hdc), width(w), height(h) {
	setupPixelFormat();
	setupOrtho2D();

	// Настройка OpenGL
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2.0f);
}

hoaOpenGlDrawer::~hoaOpenGlDrawer() = default;

void hoaOpenGlDrawer::setupOrtho2D() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, width, height, 0); // Верх-низ инвертированы
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool hoaOpenGlDrawer::setupPixelFormat() {
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		16,
		0, 0,
		PFD_MAIN_PLANE,
		0, 0, 0, 0
	};

	int pixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (pixelFormat == 0) return false;

	if (!SetPixelFormat(hDC, pixelFormat, &pfd)) return false;

	HGLRC hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	return true;
}

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
	SwapBuffers(hDC);
}
