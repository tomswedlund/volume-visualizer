#include "RadialVolume.h"
#include "Utils.h"

RadialVolume::RadialVolume(int width, int height, int depth) 
: _width(width), _height(height), _depth(depth),
  _center(width * 0.5f, height * 0.5f, depth * 0.5f) {
	int min = this->_width;
	int max = this->_height;
	Utils::minMax(min, max);
	min = this->_depth;
	Utils::minMax(min, max);
	this->_largestDim = max;
}

RadialVolume::RadialVolume(const RadialVolume& toCopy) {
	RadialVolume::copy(toCopy, *this);
}

RadialVolume::~RadialVolume() {
}

RadialVolume& RadialVolume::operator =(const RadialVolume& rhs) {
	RadialVolume::copy(rhs, *this);
	return *this;
}

float RadialVolume::density(float x, float y, float z) const {
	Vector3 point(x, y, z);
	return 0.75f * (1 - (point - this->_center).magnitude() / this->_largestDim);
}

int RadialVolume::width() const {
	return this->_width;
}

int RadialVolume::height() const {
	return this->_height;
}

int RadialVolume::depth() const {
	return this->_depth;
}

void RadialVolume::copy(const RadialVolume& from, RadialVolume& to) {
	to._width = from._width;
	to._height = from._height;
	to._depth = from._depth;
	to._center = from._center;
	to._largestDim = from._largestDim;
}
