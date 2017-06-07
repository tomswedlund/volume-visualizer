#ifndef __SphericalVolume_h__
#define __SphericalVolume_h__

#include "IVolume.h"

class SphericalVolume : public IVolume {
public:
	SphericalVolume(float radius);
	SphericalVolume(const SphericalVolume& toCopy);
	~SphericalVolume();
	SphericalVolume& operator =(const SphericalVolume& rhs);

	virtual float density(float x, float y, float z) const;
	virtual int width() const;
	virtual int height() const;
	virtual int depth() const;

private:
	void copy(const SphericalVolume& from, SphericalVolume& to);

	float _diameter, _radius;
};

#endif // __SphericalVolume_h__
