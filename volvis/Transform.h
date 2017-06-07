#ifndef __Transform_h__
#define __Transform_h__

#include "Matrix3x3.h"
#include "Vector3.h"

class Transform {
public:
	Transform();
	Transform(const Transform& toCopy);
	~Transform();
	Transform& operator =(const Transform& rhs);

	Vector3 vector() const;
	void vector(const Vector3& vector);

	Matrix3x3 matrix() const;
	void matrix(const Matrix3x3& matrix);

	Transform& translate(float x, float y, float z);
	Transform& rotate(float angle, float x, float y, float z);
	Transform& scale(float x, float y, float z);
	Transform& transform(const Transform& transform);

private:
	static void copy(const Transform& from, Transform& to);

	Matrix3x3 _matrix;
	Vector3 _vector;
};

#endif // __Transform_h__