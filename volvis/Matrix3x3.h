#ifndef __Matrix3x3_h__
#define __Matrix3x3_h__

class Vector3;

class Matrix3x3 {
public:
	static Matrix3x3 identity();

	Matrix3x3();
	Matrix3x3(const Matrix3x3& toCopy);
	~Matrix3x3();
	Matrix3x3& operator =(const Matrix3x3& rhs);

	Matrix3x3 inverse() const;
	Matrix3x3 transpose() const;

	float& operator ()(int row, int col);
	float operator ()(int row, int col) const;

	Matrix3x3& operator +=(const Matrix3x3& rhs);
	Matrix3x3& operator -=(const Matrix3x3& rhs);
	Matrix3x3& operator *=(const Matrix3x3& rhs);
	Matrix3x3& operator *=(float scalar);
	Matrix3x3& operator /=(float scalar);

	Matrix3x3 operator +(const Matrix3x3& rhs) const;
	Matrix3x3 operator -(const Matrix3x3& rhs) const;
	Matrix3x3 operator *(const Matrix3x3& rhs) const;
	Vector3 operator *(const Vector3& rhs) const;
	Matrix3x3 operator *(float scalar) const;
	Matrix3x3 operator /(float scalar) const;
	Matrix3x3 operator -() const;

private:
	static void copy(const Matrix3x3& from, Matrix3x3& to);

	float _elements[3][3];
};

#endif // __Matrix3x3_h__