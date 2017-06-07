#ifndef __PerspectiveCamera_h__
#define __PerspectiveCamera_h__

#include "ICamera.h"
#include "Transform.h"

class PerspectiveCamera : public ICamera {
public:
	PerspectiveCamera(float fov, int width, int height);
	PerspectiveCamera(const PerspectiveCamera& toCopy);
	~PerspectiveCamera();
	PerspectiveCamera& operator =(const PerspectiveCamera& rhs);

	virtual Ray generateRay(float x, float y) const;
	virtual void transform(const Transform& transform);
	virtual void setTransform(const Transform& transform);

private:
	static void copy(const PerspectiveCamera& from, PerspectiveCamera& to);

	float _halfFovInDegrees;
	int _width, _height;
	Transform _transform;
};

#endif // __PerspectiveCamera_h__