#ifndef __IVolume_h__
#define __IVolume_h__

class IVolume {
public:
	virtual float density(float x, float y, float z) const = 0;
	virtual int width() const = 0;
	virtual int height() const = 0;
	virtual int depth() const = 0;
};

#endif // __IVolume_h__