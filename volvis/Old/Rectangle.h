#ifndef __Rectangle_h__
#define __Rectangle_h__

#include "Vector.h"

class Ray;
class Transform;

class Rectangle {
public:
	Rectangle(float width, float height);
	Rectangle(const Rectangle& toCopy);
	~Rectangle();
	Rectangle& operator =(const Rectangle& rhs);

	bool intersect(const Ray& ray, Vector& point) const;
	void transform(const Transform& transform);

private:
	static void copy(const Rectangle& from, Rectangle& to);

	Vector _points[4];
	Vector _edges[4];
	Vector _normal;
};

#endif // __Rectangle_h__