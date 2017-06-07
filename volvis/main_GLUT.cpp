#include <iostream>
#include <vector>
#include <Windows.h>
#include <gl/GL.h>
#include "freeglut.h"
#include "FreeImagePlus.h"
#include "SphericalCamera.h"
#include "GLUtils.h"
#include "Utils.h"
#include "Matrix3x3.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "OrthogonalCamera.h"
#include "Image.h"
#include "IVolume.h"
#include "HomogenousVolume.h"
#include "VolumeRenderer.h"
#include "PerspectiveCamera.h"
#include "RadialVolume.h"

SphericalCamera _camera;
SphericalCamera _rayCamera;
Image _image(100, 100);
PerspectiveCamera _genCamera(90.0f, _image.width(), _image.height());
RadialVolume _volume(4, 3, 3);
BoundingBox _bbox(_volume.width(), _volume.height(), _volume.depth());

std::vector<Ray> _rays;
std::vector<Vector3> _points;

void intersect() {
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

enum MotionState {
	ROTATE,
	PAN,
	PAN_Z,
	NONE
};

void drawBoudningBox() {
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

void drawRays() {
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

void drawPoints() {
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

void drawCamera(const SphericalCamera& camera) {
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

void drawScene() {
	intersect();

	drawBoudningBox();
	drawCamera(_rayCamera);
	drawRays();
	drawPoints();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Vector3 eye(_camera.eye());
	Vector3 center(_camera.center());
	Vector3 up(_camera.up());
	gluLookAt(eye.x(), eye.y(), eye.z(),
		center.x(), center.y(), center.z(),
		up.x(), up.y(), up.z());

	drawScene();
	glutSwapBuffers();
}

void reshape(int width, int height) {
	GLUtils::setPerspectiveProjection(60.0f, width, height);
}

bool _cameraSwitch = false;
void keyboard(unsigned char key, int x, int y) {
	if (key == 's') {
		_cameraSwitch = !_cameraSwitch;
	}
	else if (key == 'r') {
		VolumeRenderer::Render(_volume, _genCamera, _image);
		_image.save("output.png");
	}
}

int _prevX = -1, _prevY = -1;
MotionState _motionState = NONE;
void mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON:
			_motionState = ROTATE;
			break;

		case GLUT_RIGHT_BUTTON:
			_motionState = PAN;
			break;

		case GLUT_MIDDLE_BUTTON:
			_motionState = PAN_Z;
			break;
		}
	}
	else {
		_motionState = NONE;
		_prevX = -1;
		_prevY = -1;
	}
}

void mouseMotion(int x, int y) {
	if (_prevX < 0) {
		_prevX = x;
	}
	if (_prevY < 0) {
		_prevY = y;
	}
	int deltaX = x - _prevX;
	int deltaY = y - _prevY;
	_prevX = x;
	_prevY = y;

	SphericalCamera* camera = 0;
	if (_cameraSwitch) {
		camera = &_rayCamera;
	}
	else {
		camera = &_camera;
	}

	switch (_motionState) {
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

void idle() {
	glutPostRedisplay();
}

void initGLUT(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CUDA Volume Visualizer");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutIdleFunc(idle);
}

void initGL() {
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////
void main_GLUT(int argc, char **argv) {
	Vector3 pos(_bbox.width() / 2.0f, _bbox.height() / 2.0f, _bbox.depth() / 2.0f);
	_camera.position(pos);
	_camera.approach(-10);

	_rayCamera.position(pos);
	//_rayCamera.approach(-5);
	_rayCamera.approach(-2);


	initGLUT(argc, argv);
	initGL();
	glutMainLoop();
}