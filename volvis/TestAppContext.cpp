#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <string>
#include "TestAppContext.h"
#include "Vector3.h"
#include "Utils.h"
#include "GLUtils.h"
#include "VolumeRenderer.h"
#include "SDLGLApp.h"
#include "SDLGLWindow.h"
#include "OutputAppContext.h"

TestAppContext::TestAppContext()
	: _image(512, 512), _state(NONE),
	_genCamera(60.0f, _image.width(), _image.height()),
	//_genCamera(_image.width(), _image.height()),
	_volume(25),/*_volume(0.1f, 25, 25, 25)*/ _cameraSwitch(false), _lookAt(false),
	_bbox(_volume.width(), _volume.height(), _volume.depth()),
	_window(nullptr) {
}

void TestAppContext::init() {
	GLUtils::setPerspectiveProjection(60.0f, _image.width(), _image.height());

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
	glPointSize(2.0f);

	Vector3 pos(_bbox.width() / 2.0f, _bbox.height() / 2.0f, _bbox.depth() / 2.0f);
	_camera.position(pos);
	_camera.approach(-10);

	_rayCamera.position(pos);
	//_rayCamera.approach(-5);
	_rayCamera.approach(-2);
}

void TestAppContext::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	SphericalCamera* camera;
	if (_lookAt) {
		camera = &_rayCamera;
	}
	else {
		camera = &_camera;
	}

	Vector3 eye(camera->eye());
	Vector3 center(camera->center());
	Vector3 up(camera->up());
	gluLookAt(eye.x(), eye.y(), eye.z(),
		center.x(), center.y(), center.z(),
		up.x(), up.y(), up.z());

	drawScene();
}

void TestAppContext::onKeyPress(int key, bool down) {
	switch (key)
	{
	case 's':
		if (down) _cameraSwitch = !_cameraSwitch;
		break;

	case 'r':
		if (down) {
			VolumeRenderer::Render(_volume, _genCamera, _image);
			_image.save("output.png");
			OutputAppContext* ctx = new OutputAppContext(&_image);
			_window->app()->createWindow(ctx);
		}
		break;
		
	case 1073742049: // shift apparently
		if (down) _state = PAN;
		else _state = NONE;
		break;

	case 1073742048: // ctrl
		_lookAt = down;
		break;
	}
}

void TestAppContext::onMouseMove(int deltaX, int deltaY) {
	SphericalCamera* camera = nullptr;
	if (_cameraSwitch) {
		camera = &_rayCamera;
	}
	else {
		camera = &_camera;
	}

	switch (_state) {
	case ROTATE:
	{
		Vector3 about;
		float angle = camera->calcAboutVector(-deltaX, -deltaY, about);
		if (angle > 0) {
			camera->rotate(angle * 0.5f, about);
		}
	}
	break;

	case PAN:
		camera->pan(0.1f * -deltaX, 0.1f * deltaY);
		break;

	case PAN_Z:
		camera->approach(0.25f * deltaY);
		break;
	}
}

void TestAppContext::onMouseButtonPress(char button, bool down) {
	if (down) {
		switch (button) {
		case 1: // left
			_state = ROTATE;
			break;

		case 2: // middle
			_state = PAN;
			break;

		case 3: // right
			_state = PAN_Z;
			break;
		}
	}
	else {
		_state = NONE;
	}
}

void TestAppContext::onWindowResize(int width, int height) {
	GLUtils::setPerspectiveProjection(60.0f, width, height);
}

void TestAppContext::cleanup() {
}

void TestAppContext::window(SDLGLWindow* w) {
	_window = w;
}

SDLGLWindow* TestAppContext::window() {
	return _window;
}

void TestAppContext::drawScene() {
	intersect();

	drawBoundingBox();
	drawCamera(_rayCamera);
	drawRays();
	drawPoints();
}

void TestAppContext::intersect() {
	_rays.clear();
	_points.clear();

	int width = 10;
	int height = 10;
	_genCamera.setTransform(_rayCamera.calcLookAt());
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			float x, y;
			Utils::transformImageCoords(width, height, i, j, x, y);
			_rays.push_back(_genCamera.generateRay(x, y));
		}
	}

	for (int i = 0; i < _rays.size(); ++i) {
		float tin, tout;
		if (_bbox.intersect(_rays[i], tin, tout)) {

			_points.push_back(_rays[i](tin));
			_points.push_back(_rays[i](tout));
		}
	}
}

void TestAppContext::drawBoundingBox() {
	// Draw the bounding box.
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, _bbox.height(), 0);

	glVertex3f(0, 0, 0);
	glVertex3f(_bbox.width(), 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, _bbox.depth());

	glVertex3f(_bbox.width(), _bbox.height(), 0);
	glVertex3f(0, _bbox.height(), 0);

	glVertex3f(_bbox.width(), _bbox.height(), 0);
	glVertex3f(_bbox.width(), 0, 0);

	glVertex3f(_bbox.width(), _bbox.height(), 0);
	glVertex3f(_bbox.width(), _bbox.height(), _bbox.depth());

	glVertex3f(0, _bbox.height(), _bbox.depth());
	glVertex3f(0, 0, _bbox.depth());

	glVertex3f(0, _bbox.height(), _bbox.depth());
	glVertex3f(_bbox.width(), _bbox.height(), _bbox.depth());

	glVertex3f(0, _bbox.height(), _bbox.depth());
	glVertex3f(0, _bbox.height(), 0);

	glVertex3f(_bbox.width(), 0, _bbox.depth());
	glVertex3f(0, 0, _bbox.depth());

	glVertex3f(_bbox.width(), 0, _bbox.depth());
	glVertex3f(_bbox.width(), _bbox.height(), _bbox.depth());

	glVertex3f(_bbox.width(), 0, _bbox.depth());
	glVertex3f(_bbox.width(), 0, 0);
	glEnd();
}

void TestAppContext::drawRays() {
	// Draw rays.
	glBegin(GL_LINES);
	glLineWidth(1);
	glColor3f(1, 0, 0);
	for (int i = 0; i < _rays.size(); ++i) {
		Vector3 origin = _rays[i].origin();
		glVertex3f(origin.x(), origin.y(), origin.z());
		Vector3 dir = _rays[i].direction();
		glVertex3f(origin.x() + dir.x(), origin.y() + dir.y(), origin.z() + dir.z());
	}
	glEnd();
}

void TestAppContext::drawCamera(const SphericalCamera& camera) {
	Vector3 eye(camera.eye());
	Vector3 x(eye + camera.x());
	Vector3 y(eye + camera.y());
	Vector3 z(eye + camera.z());

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(eye.x(), eye.y(), eye.z());
	glVertex3f(x.x(), x.y(), x.z());
	glColor3f(0, 1, 0);
	glVertex3f(eye.x(), eye.y(), eye.z());
	glVertex3f(y.x(), y.y(), y.z());
	glColor3f(0, 0, 1);
	glVertex3f(eye.x(), eye.y(), eye.z());
	glVertex3f(z.x(), z.y(), z.z());
	glEnd();

	glBegin(GL_POINTS);
	glPointSize(3.f);
	glColor3f(1, 1, 1);
	glVertex3f(camera.position().x(), camera.position().y(), camera.position().z());
	glEnd();
}

void TestAppContext::drawPoints() {
	// Draw intersection points.
	intersect();
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	glPointSize(10);
	for (int i = 0; i < _points.size(); ++i) {
		glVertex3f(_points[i].x(), _points[i].y(), _points[i].z());
	}
	glEnd();
}