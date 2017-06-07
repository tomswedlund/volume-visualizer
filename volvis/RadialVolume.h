#ifndef __RadialVolume_h__
#define __RadialVolume_h__

#include "IVolume.h"
#include "Vector3.h"

class RadialVolume : public IVolume {
public:
	RadialVolume(int width, int height, int depth);
	RadialVolume(const RadialVolume& toCopy);
	~RadialVolume();
	RadialVolume& operator =(const RadialVolume& rhs);

	virtual float density(float x, float y, float z) const;
	virtual int width() const;
	virtual int height() const;
	virtual int depth() const;

private:
	static void copy(const RadialVolume& from, RadialVolume& to);

	int _width, _height, _depth, _largestDim;
	Vector3 _center;
};

#endif // __RadialVolume_h__