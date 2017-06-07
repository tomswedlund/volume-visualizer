#include "Ray.h"
#include "Rectangle.h"
#include "Utils.h"

Rectangle::Rectangle(float width, float height) {
	_points[0] = Vector(0, 0, 0);
	_points[1] = Vector(0, height, 0);
	_points[2] = Vector(width, height, 0);
	_points[3] = Vector(width, 0, 0);

	_edges[0] = _points[1] - _points[0];
	_edges[1] = _points[2] - _points[1];
	_edges[2] = _points[3] - _points[2];
	_edges[3] = _points[0] - _points[3];

	_normal = Vector::cross(_points[1] - _points[0], _points[3] - _points[0]);
}

Rectangle::Rectangle(const Rectangle& toCopy) {
	Rectangle::copy(toCopy, *this);
}

Rectangle::~Rectangle() {
}

Rectangle& Rectangle::operator =(const Rectangle& rhs) {
	Rectangle::copy(rhs, *this);
}

bool Rectangle::intersect(const Ray& ray, Vector& point) const {
	// Calculate whether an intersection occurs anywhere on the plane.
	float denom = Vector::dot(ray.direction(), this->_normal);
	if (Utils::equals(denom, 0)) {
		return false;
	}

	// Calculate the intersection point.
	float t = Vector::dot((_points[0] - ray.direction()), this->_normal) / denom;
	point = ray(t);

	// Determine if the point is actually within the polygon.
	Vector intDir = point - _points[0];
	Vector cross = Vector::cross(_edges[0], intDir);
	
	Vector iD2 = point - _points[1];
	Vector cross2 = Vector::cross(_edges[1], iD2);
	float dot = Vector::dot(cross, cross2);

	intDir = point - _points[2];
	cross = Vector::cross(_edges[2], intDir);
	float dot2 = Vector::dot(cross2, cross);
	if ((dot / dot2) < 0) {
		return false;
	}

	iD2 = point - _points[3];
	cross2 = Vector::cross(_edges[3], id2);
	dot = Vector::dot(cross, cross2);
	if ((dot / dot2) < 0) {
		return false;
	}
}

void Rectangle::copy(const Rectangle& from, Rectangle& to) {
	for (int i = 0; i < 4; ++i) {
		to._points[i] = from._points[i];
		to._edges[i] = from._edges[i];
	}
	to._normal = from._normal;
}