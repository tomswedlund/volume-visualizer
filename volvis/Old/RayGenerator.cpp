#include <cmath>
#include "Ray.h"
#include "RayGenerator.h"
#include "Utils.h"

RayGenerator::RayGenerator(float fov, int width, int height)
: _width(width), _height(height), 
  _aspect(height / (float)width), _xStep(1 / (float)width),
  _vanishingPoint(0, 0, (0.5f / tanf(Utils::deg2rad(fov) / 2.0f))),
  _currentRow(0), _currentCol(0) {
	this->_yStep = (1 / (float)this->_height) * this->_aspect;
}

RayGenerator::RayGenerator(const RayGenerator& toCopy) {
	RayGenerator::copy(toCopy, *this);
}

RayGenerator::~RayGenerator() {
}

RayGenerator& RayGenerator::operator =(const RayGenerator& rhs) {
	RayGenerator::copy(rhs, *this);
	return *this;
}

bool RayGenerator::hasMoreRays() const {
	return (this->_currentRow < this->_height);
}

void RayGenerator::reset() {
	this->_currentCol = 0;
	this->_currentRow = 0;
}

Ray RayGenerator::generateNextRay() {
	if (!this->hasMoreRays()) {
		return Ray(Vector3(), Vector3());
	}

	float x = this->_currentCol / (float)this->_width - 0.5f + this->_xStep / 2.0f;
	float y = (this->_currentRow / (float)this->_height) * this->_aspect - (this->_aspect / 2.0f) + this->_yStep / 2.0f;

	++this->_currentCol;
	if (this->_currentCol >= this->_width) {
		this->_currentCol = 0;
		++this->_currentRow;
	}

	Vector3 origin(x, y, 0);
	Vector3 dir((origin - this->_vanishingPoint).normalize());
	return Ray(origin, dir);
}

void RayGenerator::copy(const RayGenerator& from, RayGenerator& to) {
	to._width = from._width;
	to._height = from._height;
	to._vanishingPoint = from._vanishingPoint;
}
