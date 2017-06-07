#ifndef __Integrator_h__
#define __Integrator_h__

#include "BoundingBox.h"
#include "IVolume.h"

class Ray;

class Integrator {
public:
	Integrator(const BoundingBox* bbox, const IVolume* volume);
	Integrator(const Integrator& toCopy);
	~Integrator();
	Integrator& operator =(const Integrator& rhs);

	float integrate(const Ray& ray) const;

private:
	static void copy(const Integrator& from, Integrator& to);

	const BoundingBox* _bbox;
	const IVolume* _volume;
};

#endif // __Integrator_h__