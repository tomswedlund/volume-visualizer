#ifndef __Ray_h__
#define __Ray_h__

#include "Vector3.h"

class Transform;

class Ray {
public:
	Ray(const Vector3& origin, const Vector3& direction);
	Ray(const Ray& toCopy);
	~Ray();
	Ray& operator =(const Ray& rhs);

	const Vector3& origin() const;
	void origin(const Vector3& origin);

	const Vector3& direction() const;
	void direction(const Vector3& direction);

	Ray& transform(const Transform& transform);
	Vector3 operator ()(float t) const;

private:
	static void copy(const Ray& from, Ray& to);

	Vector3 _origin, _direction;
};

#endif // _Ray_h__