#include "SphericalVolume.h"
#include "Utils.h"
#include "Vector3.h"

SphericalVolume::SphericalVolume(float diameter)
: _diameter(diameter), _radius(diameter * 0.5f) {
}

SphericalVolume::SphericalVolume(const SphericalVolume& toCopy) {
	this->copy(toCopy, *this);
}

SphericalVolume::~SphericalVolume() {
}

SphericalVolume& SphericalVolume::operator =(const SphericalVolume& rhs) {
	this->copy(rhs, *this);
	return *this;
}

float SphericalVolume::density(float x, float y, float z) const {
	Vector3 center(_radius, _radius, _radius);
	Vector3 p(x, y, z);
	float retval = (1.0f - ((p - center).magnitude() / _radius));
	retval /= 5.0f;
	Utils::clamp(retval);
	return retval;
}

int SphericalVolume::width() const {
	return _diameter;
}

int SphericalVolume::height() const {
	return _diameter;
}

int SphericalVolume::depth() const {
	return _diameter;
}

void SphericalVolume::copy(const SphericalVolume& from, SphericalVolume& to) {
	to._diameter = from._diameter;
	to._radius = from._radius;
}
