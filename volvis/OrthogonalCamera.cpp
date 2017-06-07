#include "OrthogonalCamera.h"

OrthogonalCamera::OrthogonalCamera(int width, int height)
: _width(width), _height(height) {
}

OrthogonalCamera::OrthogonalCamera(const OrthogonalCamera& toCopy) {
	OrthogonalCamera::copy(toCopy, *this);
}

OrthogonalCamera::~OrthogonalCamera() {
}

OrthogonalCamera& OrthogonalCamera::operator =(const OrthogonalCamera& rhs) {
	OrthogonalCamera::copy(rhs, *this);
	return *this;
}

Ray OrthogonalCamera::generateRay(float x, float y) const {
	Vector3 origin(x, y, 0);
	Vector3 direction(0, 0, -1);
	Ray ray(origin, direction);
	return ray.transform(this->_transform);
}

void OrthogonalCamera::transform(const Transform& transform) {
	this->_transform.transform(transform);
}

void OrthogonalCamera::setTransform(const Transform& transform) {
	this->_transform = transform;
}

void OrthogonalCamera::copy(const OrthogonalCamera& from, OrthogonalCamera& to) {
	to._width = from._width;
	to._height = from._height;
}