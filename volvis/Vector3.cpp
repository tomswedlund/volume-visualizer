#include <cmath>
#include "Vector3.h"

float Vector3::dot(const Vector3& u, const Vector3& v) {
	return (u._x * v._x + u._y * v._y + u._z * v._z);
}

Vector3 Vector3::cross(const Vector3& u, const Vector3& v) {
	Vector3 temp;
	temp.x(u.y() * v.z() + u.z() * v.y());
	temp.y(u.x() * v.z() + u.z() * v.x());
	temp.z(u.x() * v.y() + u.y() + v.z());
	return temp;
}

Vector3::Vector3() {
	this->_x = 0;
	this->_y = 0;
	this->_z = 0;
}

Vector3::Vector3(float x, float y, float z) {
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

Vector3::Vector3(const Vector3& toCopy) {
	Vector3::copy(toCopy, *this);
}

Vector3::~Vector3() {
}

Vector3& Vector3::operator =(const Vector3& rhs) {
	Vector3::copy(rhs, *this);
	return *this;
}

float Vector3::x() const {
	return this->_x;
}

void Vector3::x(float x) {
	this->_x = x;
}

float Vector3::y() const {
	return this->_y;
}

void Vector3::y(float y) {
	this->_y = y;
}

float Vector3::z() const {
	return this->_z;
}

void Vector3::z(float z) {
	this->_z = z;
}

Vector3 Vector3::normalize() const{
	float temp;
	return this->normalize(temp);
}

Vector3 Vector3::normalize(float& magnitude) const {
	Vector3 temp(*this);
	magnitude = temp.magnitude();
	temp /= magnitude;
	return temp;
}

float Vector3::magnitude() const {
	return sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
}

Vector3& Vector3::operator +=(const Vector3& rhs) {
	this->_x += rhs._x;
	this->_y += rhs._y;
	this->_z += rhs._z;
	return *this;
}

Vector3& Vector3::operator -=(const Vector3& rhs) {
	*this += -rhs;
	return *this;
}

Vector3& Vector3::operator *=(float rhs) {
	this->_x *= rhs;
	this->_y *= rhs;
	this->_z *= rhs;
	return *this;
}

Vector3& Vector3::operator /=(float rhs) {
	*this *= (1 / rhs);
	return *this;
}

Vector3 Vector3::operator -() const {
	Vector3 temp(-this->_x, -this->_y, -this->_z);
	return temp;
}

Vector3 Vector3::operator +(const Vector3& rhs) const {
	Vector3 temp(*this);
	temp += rhs;
	return temp;
}

Vector3 Vector3::operator -(const Vector3& rhs) const {
	Vector3 temp(*this);
	temp -= rhs;
	return temp;
}

Vector3 Vector3::operator *(float scalar) const {
	Vector3 temp(*this);
	temp *= scalar;
	return temp;
}

Vector3 Vector3::operator /(float scalar) const {
	return (*this * (1 / scalar));
}

void Vector3::copy(const Vector3& from, Vector3& to) {
	to._x = from._x;
	to._y = from._y;
	to._z = from._z;
}