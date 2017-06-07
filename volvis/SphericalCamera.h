#ifndef __SphericalCamera_h__
#define __SphericalCamera_h__

class Transform;

#include "Vector3.h"

class SphericalCamera {
public:
	SphericalCamera();
	SphericalCamera(const SphericalCamera& toCopy);
	~SphericalCamera();
	SphericalCamera& operator =(const SphericalCamera& rhs);

	void approach(float z);
	void pan(float x, float y);
	void rotate(float angle, const Vector3& about);
	float calcAboutVector(float deltaX, float deltaY, Vector3& about) const;

	void position(const Vector3& position);
	Vector3 position() const;

	Vector3 eye() const;
	Vector3 center() const;
	Vector3 up() const;

	Transform calcLookAt() const;

	Vector3 x() const;
	Vector3 y() const;
	Vector3 z() const;

private:
	static void copy(const SphericalCamera& from, SphericalCamera& to);

	float _radius;
	Vector3 _x, _y, _z, _position;
};

#endif // __SphericalCamera_h__