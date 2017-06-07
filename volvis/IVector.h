#ifndef __IVector_h__
#define __IVector_h__

class IVector
{
public:
	virtual float x() const = 0;
	virtual float y() const = 0;
	virtual float z() const = 0;
};

#endif // __IVector_h__