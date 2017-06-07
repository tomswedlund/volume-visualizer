#ifndef __Image_h__
#define __Image_h__

#include <string>
#include <FreeImage\FreeImagePlus.h>
#include "Color.h"

class Image {
public:
	Image(const std::string& path);
	Image(int width, int height);
	Image(const Image& toCopy);
	~Image();
	Image& operator =(const Image& rhs);

	void set(int x, int y, const Color& color);
	Color get(int x, int y) const;

	int width() const;
	int height() const;

	void save(const std::string& path) const;
	unsigned char* raw() const;

	unsigned int bpp() const;
	FREE_IMAGE_COLOR_TYPE colorType() const;

private:
	static void copy(const Image& from, Image& to);

	fipImage _image;
};

#endif // __Image_h__