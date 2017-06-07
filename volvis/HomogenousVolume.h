#ifndef __HomogenousVolume_h__
#define __HomogenousVolume_h__

#include "IVolume.h"

class HomogenousVolume : public IVolume {
public:
	HomogenousVolume(float density, int width, int height, int depth);
	HomogenousVolume(const HomogenousVolume& toCopy);
	~HomogenousVolume();
	HomogenousVolume& operator =(const HomogenousVolume& rhs);

	virtual float density(float x, float y, float z) const;
	virtual int width() const;
	virtual int height() const;
	virtual int depth() const;

private:
	static void copy(const HomogenousVolume& from, HomogenousVolume& to);

	float _density;
	int _width, _height, _depth;
};

#endif // __HomogenousVolume_h__