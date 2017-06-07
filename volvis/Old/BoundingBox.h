#ifndef __BoundingBox_h__
#define __BoundingBox_h__

#include "Vector3.h"

class Ray;

class BoundingBox {
public:
	BoundingBox(float width, float height, float depth);
	BoundingBox(const BoundingBox& toCopy);
	~BoundingBox();
	BoundingBox& operator =(const BoundingBox& rhs);

	bool intersect(const Ray& ray, float& tIn, float& tOut) const;

private:
	static void copy(const BoundingBox& from, BoundingBox& to);

	float _width, _height, _depth;
	Vector3 _normals[6];
	Vector3 _bottomFrontLeft, _topBackRight;
};



#endif // __BoundingBox_h__