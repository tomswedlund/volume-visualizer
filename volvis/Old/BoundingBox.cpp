#include "BoundingBox.h"
#include "Ray.h"
#include "Utils.h"

namespace {
	void determineCorner(int normalIndex, const Vector3& bfl, const Vector3& tbr,
		Vector3& corner) {
		corner = bfl;
		switch (normalIndex) {
		case 1:
		case 2:
		case 3:
			corner = tbr;
			break;
		}
	}

	bool compareBounds(int normalIndex, const Vector3& point, 
		float width, float height, float depth) {
		switch (normalIndex) {
		// along z-zxis
		case 0:
		case 1:
			return ((point.x() >= 0) && (point.x() <= width) &&
				(point.y() >= 0) && (point.y() <= height));
			break;

		// along y-axis
		case 2:
		case 4:
			return ((point.x() >= 0) && (point.x() <= width) &&
				(point.z() >= 0) && (point.z() <= depth));
			break;

		// along x-axis
		case 3:
		case 5:
			return ((point.y() >= 0) && (point.y() <= height) &&
				(point.z() >= 0) && (point.z() <= depth));
			break;
		}
	}
}

BoundingBox::BoundingBox(float width, float height, float depth)
: _width(width), _height(height), _depth(depth) {
	this->_normals[0] = Vector3(0, 0, 1);
	this->_normals[1] = Vector3(0, 0, -1);
	this->_normals[2] = Vector3(0, 1, 0);
	this->_normals[3] = Vector3(1, 0, 0);
	this->_normals[4] = Vector3(0, -1, 0);
	this->_normals[5] = Vector3(-1, 0, 0);

	/*float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	float halfDepth = depth / 2.0f;
	this->_bottomFrontLeft = Vector3(-halfWidth, -halfHeight, halfDepth);
	this->_topBackRight = Vector3(halfWidth, halfHeight, -halfDepth);*/
	this->_bottomFrontLeft = Vector3(0, 0, 0);
	this->_topBackRight = Vector3(width, height, depth);
}

BoundingBox::BoundingBox(const BoundingBox& toCopy) {
	BoundingBox::copy(toCopy, *this);
}

BoundingBox::~BoundingBox() {
}

BoundingBox& BoundingBox::operator =(const BoundingBox& rhs) {
	BoundingBox::copy(rhs, *this);
	return *this;
}

bool BoundingBox::intersect(const Ray& ray, float& tIn, float& tOut) const {
	bool foundIn = false;
	for (int i = 0; i < 6; ++i) {
		// Make sure the denominator is > 0.
		float denom = Vector3::dot(ray.direction(), this->_normals[i]);
		if (Utils::equals(denom, 0)) {
			continue;
		}

		Vector3 corner;
		determineCorner(i, _bottomFrontLeft, _topBackRight, corner);
		float t = Vector3::dot(this->_normals[i], (corner - ray.origin())) / denom;

		Vector3 point = ray(t);
		if (compareBounds(i, point, this->_width, this->_height, this->_depth)) {
			if (!foundIn) {
				tIn = t;
				foundIn = true;
			}
			else {
				tOut = t;
				break;
			}
		}
	}

	if (foundIn) {
		Utils::minMax(tIn, tOut);
	}
	return foundIn;
}

void BoundingBox::copy(const BoundingBox& from, BoundingBox& to) {
	to._width = from._width;
	to._height = from._height;
	to._depth = from._depth;

	for (int i = 0; i < 6; ++i) {
		to._normals[i] = from._normals[i];
	}
}