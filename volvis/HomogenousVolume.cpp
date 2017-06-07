#include "HomogenousVolume.h"

HomogenousVolume::HomogenousVolume(float density, int width, int height, int depth)
: _density(density),
  _width(width),
  _height(height),
  _depth(depth) {
}

HomogenousVolume::HomogenousVolume(const HomogenousVolume& toCopy) {
	HomogenousVolume::copy(toCopy, *this);
}

HomogenousVolume::~HomogenousVolume() {
}

HomogenousVolume& HomogenousVolume::operator =(const HomogenousVolume& rhs) {
	HomogenousVolume::copy(rhs, *this);
	return *this;
}

float HomogenousVolume::density(float x, float y, float z) const {
	return this->_density;
}

int HomogenousVolume::width() const {
	return this->_width;
}

int HomogenousVolume::height() const {
	return this->_height;
}

int HomogenousVolume::depth() const {
	return this->_depth;
}

void HomogenousVolume::copy(const HomogenousVolume& from, HomogenousVolume& to) {
	to._density = from._density;
}