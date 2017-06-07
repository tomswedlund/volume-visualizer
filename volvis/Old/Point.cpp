#include "Point.h"

Point::Point() {
}

Point::Point(float x, float y, float z)
: _vector(x, y, z) {
}

Point::Point(const Point& toCopy) {
	Point::copy(toCopy, *this);
}

Point::~Point() {
}

Point& Point::operator =(const Point& rhs) {
	Point::copy(rhs, *this);
	return *this;
}

float Point::x() const {
	return this->_vector.x();
}

void Point::x(float x) {
	this->_vector.x(x);
}

float Point::y() const {
	return this->_vector.y();
}

void Point::y(float y) {
	this->_vector.y(y);
}

float Point::z() const {
	return this->_vector.z();
}

void Point::z(float z) {
	this->_vector.z(z);
}

Point& Point::operator +=(const Vector& vector) {
	this->_vector += vector;
	return *this;
}

Point& Point::operator -=(const Vector& vector) {
	this->_vector -= vector;
	return *this;
}

Point Point::operator +(const Vector& vector) const {
	Point temp(*this);
	temp += vector;
	return temp;
}

Point Point::operator -(const Vector& vector) const {
	Point temp(*this);
	temp -= vector;
	return temp;
}

Vector Point::operator -(const Point& point) const {
	Vector temp(this->_vector);
	temp -= point._vector;
	return temp;
}

void Point::copy(const Point& from, Point& to) {
	to._vector = from._vector;
}