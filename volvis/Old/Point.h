#ifndef __Point_h__
#define __Point_h__

#include "Vector.h"

class Point {
public:
	Point();
	Point(float x, float y, float z);
	Point(const Point& toCopy);
	~Point();
	Point& operator =(const Point& rhs);

	float x() const;
	void x(float x);

	float y() const;
	void y(float y);

	float z() const;
	void z(float z);

	Point& operator +=(const Vector& vector);
	Point& operator -=(const Vector& vector);

	Point operator +(const Vector& vector) const;
	Point operator -(const Vector& vector) const;
	Vector operator -(const Point& point) const;

private:
	static void copy(const Point& from, Point& to);

	Vector _vector;
};

#endif // __Point_h__