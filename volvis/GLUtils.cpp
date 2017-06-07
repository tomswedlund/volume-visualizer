#include <cmath>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GLUtils.h"

namespace {
	const float PI = 3.1415926535897932384626433832795f;
}

void GLUtils::setPerspectiveProjection(float fov, int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (float)(width) / height, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLUtils::setOthoProjection(int width, int height) {
	glViewport((GLsizei)0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
