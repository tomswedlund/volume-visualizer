#include "Color.h"

Color::Color(float r, float g, float b, float a)
: _r(r), _g(g), _b(b), _a(a) {
}

Color::Color(const Color& toCopy) {
	Color::copy(toCopy, *this);
}

Color::~Color() {
}

Color& Color::operator =(const Color& rhs) {
	Color::copy(rhs, *this);
	return *this;
}

void Color::r(float r) {
	this->_r = r;
}

float Color::r() const {
	return this->_r;
}

void Color::g(float g) {
	this->_g = g;
}

float Color::g() const {
	return this->_g;
}

void Color::b(float b) {
	this->_b = b;
}

float Color::b() const {
	return this->_b;
}

void Color::a(float a) {
	this->_a = a;
}

float Color::a() const {
	return this->_a;
}

void Color::copy(const Color& from, Color& to) {
	to._r = from._r;
	to._g = from._g;
	to._b = from._b;
	to._a = from._a;
}