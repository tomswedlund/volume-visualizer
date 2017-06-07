#include <cmath>
#include "PerspectiveCamera.h"
#include "Utils.h"

PerspectiveCamera::PerspectiveCamera(float fov, int width, int height)
: _halfFovInDegrees(Utils::deg2rad(fov) * 0.5f), _width(width), _height(height) {
}

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& toCopy) {
	PerspectiveCamera::copy(toCopy, *this);
}

PerspectiveCamera::~PerspectiveCamera() {
}

PerspectiveCamera& PerspectiveCamera::operator =(const PerspectiveCamera& rhs) {
	PerspectiveCamera::copy(rhs, *this);
	return *this;
}

Ray PerspectiveCamera::generateRay(float x, float y) const {
	Vector3 origin(x, y, 0);
	// NOTE: this assumes the width of the image plane is 1.
	float dist = 0.5f / tanf(this->_halfFovInDegrees);
	Vector3 vanishingPoint(0, 0, dist);
	Ray ray(origin, (origin - vanishingPoint).normalize());
	return ray.transform(this->_transform);
}

void PerspectiveCamera::transform(const Transform& transform) {
	this->_transform.transform(transform);
}

void PerspectiveCamera::setTransform(const Transform& transform) {
	this->_transform = transform;
}

void PerspectiveCamera::copy(const PerspectiveCamera& from, PerspectiveCamera& to) {
	to._halfFovInDegrees = from._halfFovInDegrees;
	to._width = from._width;
	to._height = from._height;
}
