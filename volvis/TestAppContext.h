#ifndef __TestAppContext_h__
#define __TestAppContext_h__

#include "IAppContext.h"
#include "SphericalCamera.h"
#include "Image.h"
#include "PerspectiveCamera.h"
#include "OrthogonalCamera.h"
#include "RadialVolume.h"
#include "SphericalVolume.h"
#include "HomogenousVolume.h"
#include "BoundingBox.h"
#include <vector>

class TestAppContext : public IAppContext {
public:
	TestAppContext();

	virtual void init();
	virtual void render();
	virtual void onKeyPress(int key, bool down);
	virtual void onMouseMove(int deltaX, int deltaY);
	virtual void onMouseButtonPress(char button, bool down);
	virtual void onWindowResize(int width, int height);
	virtual void cleanup();

	virtual void window(SDLGLWindow* w);
	virtual SDLGLWindow* window();

private:
	enum MotionState {
		ROTATE,
		PAN,
		PAN_Z,
		NONE
	};

	SphericalCamera _camera;
	SphericalCamera _rayCamera;
	Image _image;
	PerspectiveCamera _genCamera;
	SphericalVolume _volume;
	BoundingBox _bbox;
	std::vector<Ray> _rays;
	std::vector<Vector3> _points;
	MotionState _state;
	bool _cameraSwitch;
	bool _lookAt;
	SDLGLWindow* _window;

	void drawScene();
	void intersect();
	void drawBoundingBox();
	void drawCamera(const SphericalCamera& camera);
	void drawRays();
	void drawPoints();
};

#endif // __TestAppContext_h__