#include "Ray.h"
#include "Transform.h"

Ray::Ray(const Vector3& origin, const Vector3& direction)
: _origin(origin), _direction(direction.normalize()) {
}

Ray::Ray(const Ray& toCopy) {
	Ray::copy(toCopy, *this);
}

Ray::~Ray() {
}

Ray& Ray::operator =(const Ray& rhs) {
	Ray::copy(rhs, *this);
	return *this;
}

const Vector3& Ray::origin() const {
	return this->_origin;
}

void Ray::origin(const Vector3& origin) {
	this->_origin = origin;
}

const Vector3& Ray::direction() const {
	return this->_direction;
}

void Ray::direction(const Vector3& direction) {
	this->_direction = direction;
}

Ray& Ray::transform(const Transform& transform) {
	/*Vector3 origin(transform.matrix() * this->_origin + transform.vector());
	Vector3 direction(transform.matrix().inverse().transpose() * this->_direction);
	return Ray(origin, direction);*/

	this->_origin = transform.matrix() * this->_origin + transform.vector();
	this->_direction = transform.matrix().inverse().transpose() * this->_direction;
	return *this;
}

Vector3 Ray::operator ()(float t) const {
	return this->_origin + (this->_direction * t);
}

void Ray::copy(const Ray& from, Ray& to) {
	to._origin = from._origin;
	to._direction = from._direction;
}