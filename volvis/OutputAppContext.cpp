#include <Windows.h>
#include <gl/GL.h>
#include "GLUtils.h"
#include "Image.h"
#include "OutputAppContext.h"

OutputAppContext::OutputAppContext(Image* image)
: _image(image), _window(nullptr), _textureId(0) {
}

void OutputAppContext::init() {
	GLUtils::setOthoProjection(_image->width(), _image->height());

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _image->width(), _image->height(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, _image->raw());

	GLenum error = glGetError();

	
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//glDisable(GL_TEXTURE_2D);
}

void OutputAppContext::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1);	glVertex3f(0, _image->height(), 0);
	glTexCoord2f(1, 1);	glVertex3f(_image->width(), _image->height(), 0);
	glTexCoord2f(1, 0); glVertex3f(_image->width(), 0, 0);
	glEnd();

	glFlush();
	

	/*glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0, _image->height(), 0);
	glTexCoord2f(1, 0);
	glVertex3f(_image->width(), _image->height(), 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(_image->width(), 0, 0);
	glEnd();*/
}

void OutputAppContext::onKeyPress(int key, bool down) {

}

void OutputAppContext::onMouseMove(int deltaX, int deltaY) {

}

void OutputAppContext::onMouseButtonPress(char button, bool down) {

}

void OutputAppContext::onWindowResize(int width, int height) {

}

void OutputAppContext::cleanup() {
}

void OutputAppContext::window(SDLGLWindow* w) {
	_window = w;
}

SDLGLWindow* OutputAppContext::window() {
	return _window;
}
