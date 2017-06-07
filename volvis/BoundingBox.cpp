#include "BoundingBox.h"
#include "Ray.h"
#include "Utils.h"

namespace {
	bool checkPlaneBounds(float t, float bounds) {
		return ((t >= 0) && (t <= bounds));
	}
}

BoundingBox::BoundingBox(float width, float height, float depth)
: _width(width), _height(height), _depth(depth) {
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
	float result[2];
	int tIndex = 0;

	for (int i = 0; i < 3; ++i) {
		switch (i) {
		case 0: // x
			if (!Utils::equals(ray.direction().x(), 0)) {
				// Positive normal.
				float t = (this->_width - ray.origin().x()) / ray.direction().x();
				Vector3 point(ray(t));
				if (checkPlaneBounds(point.y(), this->_height) &&
					checkPlaneBounds(point.z(), this->_depth)) {
					result[tIndex] = t;
					++tIndex;
				}

				// Negative normal.
				t = -ray.origin().x() / ray.direction().x();
				point = ray(t);
				if (checkPlaneBounds(point.y(), this->_height) &&
					checkPlaneBounds(point.z(), this->_depth)) {
					result[tIndex] = t;
					++tIndex;
				}
			}
			break;

		case 1: // y
			if (!Utils::equals(ray.direction().y(), 0)) {
				// Positive normal.
				float t = (this->_height - ray.origin().y()) / ray.direction().y();
				Vector3 point(ray(t));
				if (checkPlaneBounds(point.x(), this->_width) &&
					checkPlaneBounds(point.z(), this->_depth)) {
					result[tIndex] = t;
					++tIndex;
				}

				// Negative normal.
				if (tIndex < 2) {
					t = -ray.origin().y() / ray.direction().y();
					point = ray(t);
					if (checkPlaneBounds(point.x(), this->_width) &&
						checkPlaneBounds(point.z(), this->_depth)) {
						result[tIndex] = t;
						++tIndex;
					}
				}
			}
			break;

		case 2: // z
			if (!Utils::equals(ray.direction().z(), 0)) {
				// Positive normal.
				float t = (this->_depth - ray.origin().z()) / ray.direction().z();
				Vector3 point(ray(t));
				if (checkPlaneBounds(point.x(), this->_width) &&
					checkPlaneBounds(point.y(), this->_height)) {
					result[tIndex] = t;
					++tIndex;
				}

				// Negative normal.
				if (tIndex < 2) {
					t = -ray.origin().z() / ray.direction().z();
					point = ray(t);
					if (checkPlaneBounds(point.x(), this->_width) &&
						checkPlaneBounds(point.y(), this->_height)) {

						result[tIndex] = t;
						++tIndex;
					}
				}
			}
			break;
		}

		// Found both t's, nothing left to do.
		if (tIndex == 2) {
			break;
		}
	}

	if (tIndex == 2) {
		Utils::minMax(result[0], result[1]);
		tIn = result[0];
		tOut = result[1];

		if (tOut < 0) {
			return false;
		}
		if (tIn < 0) {
			tIn = 0;
		}
		return true;
	}
	else {
		return false;
	}
}

float BoundingBox::width() const {
	return this->_width;
}

float BoundingBox::height() const {
	return this->_height;
}

float BoundingBox::depth() const {
	return this->_depth;
}

void BoundingBox::copy(const BoundingBox& from, BoundingBox& to) {
	to._width = from._width;
	to._height = from._height;
	to._depth = from._depth;
}