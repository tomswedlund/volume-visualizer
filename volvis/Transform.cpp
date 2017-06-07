#include "Transform.h"
#include "Utils.h"

Transform::Transform()
	: _matrix(Matrix3x3::identity()) {
}

Transform::Transform(const Transform& toCopy) {
	Transform::copy(toCopy, *this);
}

Transform::~Transform() {
}

Transform& Transform::operator =(const Transform& rhs) {
	Transform::copy(rhs, *this);
	return *this;
}

Vector3 Transform::vector() const {
	return this->_vector;
}

void Transform::vector(const Vector3& vector) {
	this->_vector = vector;
}

Matrix3x3 Transform::matrix() const {
	return this->_matrix;
}

void Transform::matrix(const Matrix3x3& matrix) {
	this->_matrix = matrix;
}

Transform& Transform::translate(float x, float y, float z) {
	Vector3 tr(x, y, z);
	this->_vector = this->_matrix * tr + this->_vector;
	return *this;
}

Transform& Transform::rotate(float angle, float x, float y, float z) {
	Vector3 rotVec(x, y, z);
	this->_matrix *= Utils::createRotateMatrix(angle, rotVec);
	return *this;
}

Transform& Transform::scale(float x, float y, float z) {
	Matrix3x3 temp;
	temp(0, 0) = x;
	temp(1, 1) = y;
	temp(2, 2) = z;
	this->_matrix *= temp;
	return *this;
}

Transform& Transform::transform(const Transform& transform) {
	this->_vector = this->_matrix * transform._vector + this->_vector;
	this->_matrix = this->_matrix * transform._matrix;
	return *this;
}

void Transform::copy(const Transform& from, Transform& to) {
	to._matrix = from._matrix;
	to._vector = from._vector;
}