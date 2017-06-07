#include "Integrator.h"
#include "Ray.h"
#include "Utils.h"

Integrator::Integrator(const BoundingBox* bbox, const IVolume* volume)
: _bbox(bbox), _volume(volume) {
}

Integrator::Integrator(const Integrator& toCopy) {
	Integrator::copy(toCopy, *this);
}

Integrator::~Integrator() {
}

Integrator& Integrator::operator =(const Integrator& rhs) {
	Integrator::copy(rhs, *this);
	return *this;
}

float Integrator::integrate(const Ray& ray) const {
	float tIn, tOut;
	float density = 0;
	if (_bbox->intersect(ray, tIn, tOut)) {
		const float step = 0.5f;
		float t = tIn;
		float a = 0;
		while (t <= tOut) {
			float jitteredT = Utils::jitter(t, step);
			if (jitteredT > tOut) {
				break;
			}
			Vector3 jitteredPoint = ray(jitteredT);
			float volDensity = _volume->density(jitteredPoint.x(), jitteredPoint.y(), jitteredPoint.z());
			density += (volDensity * (1 - a));
			a += (volDensity * (1 - a));
			t += step;
		}
	}
	return density;

	//float tIn, tOut;
	//float density = 0;
	//if (this->_bbox->intersect(ray, tIn, tOut)) {
	//	const float step = 0.1f;
	//	const float alpha = 0;
	//	float t = tIn;
	//	float a = alpha;
	//	while (t <= tOut) {
	//		float jitteredT = Utils::jitter(t, step);
	//		if (jitteredT > tOut) {
	//			break;
	//		}
	//		Vector3 jitteredPoint = ray(jitteredT);
	//		float volDensity = this->_volume->density(jitteredPoint.x(), jitteredPoint.y(), jitteredPoint.z());
	//		//return volDensity;
	//		/*if (volDensity > 0.01f) return 1;
	//		else return 0;*/
	//		density += (1 - a) * volDensity * volDensity;
	//		a += (1 - a) * volDensity;
	//		t += step;
	//	}
	//}
	//return density;
}

void Integrator::copy(const Integrator& from, Integrator& to) {
	to._bbox = from._bbox;
	to._volume = from._volume;
}