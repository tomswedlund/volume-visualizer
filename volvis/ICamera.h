#ifndef __ICamera_h__
#define __ICamera_h__

#include "Ray.h"

class Transform;

class ICamera {
public:
	virtual Ray generateRay(float x, float y) const = 0;
	virtual void transform(const Transform& transform) = 0;
	virtual void setTransform(const Transform& transform) = 0;
};

#endif // __ICamera_h__