#include <cmath>
#include "SphericalCamera.h"
#include "Matrix3x3.h"
#include "Transform.h"
#include "Utils.h"

SphericalCamera::SphericalCamera() {
	_x.x(1);
	_y.y(1);
	_z.z(1);
	_radius = 0;
}

SphericalCamera::SphericalCamera(const SphericalCamera& toCopy) {
	SphericalCamera::copy(toCopy, *this);
}

SphericalCamera::~SphericalCamera() {
}

SphericalCamera& SphericalCamera::operator =(const SphericalCamera& rhs) {
	SphericalCamera::copy(rhs, *this);
	return *this;
}

void SphericalCamera::approach(float z) {
	this->_radius -= z;
	if (this->_radius <= 0) {
		this->_radius = 0.1f;
	}
}

void SphericalCamera::pan(float x, float y) {
	this->_position += (this->_x * x + this->_y * y);
}

void SphericalCamera::rotate(float angle, const Vector3& about) {
	Matrix3x3 rotMat(Utils::createRotateMatrix(angle, about));
	this->_x = (rotMat * this->_x).normalize();
	this->_y = (rotMat * this->_y).normalize();
	this->_z = (rotMat * this->_z).normalize();
}

float SphericalCamera::calcAboutVector(float deltaX, float deltaY, Vector3& about) const {
	about = this->_x * deltaY + this->_y * deltaX;
	float mag;
	about = about.normalize(mag);
	return mag;
}

void SphericalCamera::position(const Vector3& position) {
	this->_position = position;
}

Vector3 SphericalCamera::position() const {
	return this->_position;
}

Vector3 SphericalCamera::eye() const {
	return (this->_position + this->_z * this->_radius);
}

Vector3 SphericalCamera::center() const { 
	return this->_position;
}

Vector3 SphericalCamera::up() const {
	return this->_y;
}

Transform SphericalCamera::calcLookAt() const {
	Matrix3x3 matrix;
	matrix(0, 0) = this->_x.x(); matrix(1, 0) = this->_x.y(); matrix(2, 0) = this->_x.z();
	matrix(0, 1) = this->_y.x(); matrix(1, 1) = this->_y.y(); matrix(2, 1) = this->_y.z();
	matrix(0, 2) = this->_z.x(); matrix(1, 2) = this->_z.y(); matrix(2, 2) = this->_z.z();
	
	Transform transform;
	transform.matrix(matrix);
	transform.vector(this->eye());
	return transform;
}

Vector3 SphericalCamera::x() const {
	return this->_x;
}

Vector3 SphericalCamera::y() const {
	return this->_y;
}

Vector3 SphericalCamera::z() const {
	return this->_z;
}

void SphericalCamera::copy(const SphericalCamera& from, SphericalCamera& to) {
	to._x = from._x;
	to._y = from._y;
	to._z = from._z;
	to._position = from._position;
	to._radius = from._radius;
}