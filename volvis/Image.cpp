#include <string>
#include "Color.h"
#include "Image.h"

namespace {
	unsigned char convert(float channel) {
		if (channel > 1) channel = 1;
		if (channel < 0) channel = 0;
		return (unsigned char)(channel * 255);
	}
}

Image::Image(const std::string& path)
: _image() {
	_image.load(path.c_str());
	unsigned int bpp = _image.getBitsPerPixel();
	FREE_IMAGE_COLOR_TYPE type = _image.getColorType();
	FREE_IMAGE_TYPE imType = _image.getImageType();
}

Image::Image(int width, int height)
: _image(FIT_BITMAP, width, height, 24) {
}

Image::Image(const Image& toCopy) {
	Image::copy(toCopy, *this);
}

Image::~Image() {
}

Image& Image::operator =(const Image& rhs) {
	Image::copy(rhs, *this);
	return *this;
}

void Image::set(int x, int y, const Color& color) {
	RGBQUAD quad = { convert(color.r()), convert(color.g()), convert(color.b()), 0 };
	this->_image.setPixelColor(x, this->_image.getWidth() - y, &quad);
}

Color Image::get(int x, int y) const {
	RGBQUAD quad;
	this->_image.getPixelColor(x, this->_image.getWidth() - y, &quad);
	return Color(quad.rgbRed, quad.rgbGreen, quad.rgbBlue);
	return Color(0, 0, 0);
}

int Image::width() const {
	return this->_image.getWidth();
	return 0;
}

int Image::height() const {
	return this->_image.getHeight();
	return 0;
}

void Image::save(const std::string& path) const {
	this->_image.save(path.c_str());
}

unsigned char* Image::raw() const {
	auto pixels = _image.accessPixels();
	int width = _image.getWidth();
	int height = _image.getHeight();
	return _image.accessPixels();
}

unsigned int Image::bpp() const {
	return _image.getBitsPerPixel();
}

FREE_IMAGE_COLOR_TYPE Image::colorType() const {
	return _image.getColorType();
}

void Image::copy(const Image& from, Image& to) {
	// TODO: not actually sure how FreeImage copies images.
	// But, to be honest, I don't care. 
	to._image = from._image;
}