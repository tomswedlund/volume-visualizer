#ifndef __Vector3_h__
#define __Vector3_h__

class Vector3 {
public:
	static float dot(const Vector3& u, const Vector3& v);
	static Vector3 cross(const Vector3& u, const Vector3& v);

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& toCopy);
	~Vector3();
	Vector3& operator =(const Vector3& rhs);

	virtual float x() const;
	void x(float x);

	virtual float y() const;
	void y(float y);

	virtual float z() const;
	void z(float z);

	Vector3 normalize() const;
	Vector3 normalize(float& magnitude) const;
	float magnitude() const;

	Vector3& operator +=(const Vector3& rhs);
	Vector3& operator -=(const Vector3& rhs);
	Vector3& operator *=(float rhs);
	Vector3& operator /=(float rhs);
	Vector3 operator -() const;

	Vector3 operator +(const Vector3& rhs) const;
	Vector3 operator -(const Vector3& rhs) const;
	Vector3 operator *(float scalar) const;
	Vector3 operator /(float scalar) const;

private:
	static void copy(const Vector3& from, Vector3& to);

	float _x, _y, _z;
};

#endif // __Math_Vector3_h__