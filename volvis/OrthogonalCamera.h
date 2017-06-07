#ifndef __OrthogonalCamera_h__
#define __OrthogonalCamera_h__

#include "ICamera.h"
#include "Transform.h"

class OrthogonalCamera : public ICamera {
public:
	OrthogonalCamera(int width, int height);
	OrthogonalCamera(const OrthogonalCamera& toCopy);
	~OrthogonalCamera();
	OrthogonalCamera& operator =(const OrthogonalCamera& rhs);

	virtual Ray generateRay(float x, float y) const;
	virtual void transform(const Transform& transform);
	virtual void setTransform(const Transform& transform);

private:
	static void copy(const OrthogonalCamera& from, OrthogonalCamera& to);

	int _width, _height;
	Transform _transform;
};

#endif // __OrthogonalCamera_h__