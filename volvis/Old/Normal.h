#ifndef __Normal_h__
#define __Normal_h__

class Normal
{
	Normal(float x, float y, float z);
	Normal(const Vector& rhs);
	Normal(const Normal& toCopy);
	~Normal();
	Normal& operator =(const Normal& rhs);

	float x() const;
	float y() const;
	float z() const;
};

#endif // __Normal_h__