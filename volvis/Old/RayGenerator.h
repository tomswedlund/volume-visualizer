#ifndef __RayGenerator_h__
#define __RayGenerator_h__

class Ray;

class RayGenerator {
public:
	RayGenerator(float fov, int width, int height);
	RayGenerator(const RayGenerator & toCopy);
	~RayGenerator();
	RayGenerator& operator =(const RayGenerator& rhs);

	bool hasMoreRays() const;

	void reset();
	Ray generateNextRay();

private:
	static void copy(const RayGenerator& from, RayGenerator& to);

	int _width, _height, _currentRow, _currentCol;
	float _xStep, _yStep, _aspect;
	Vector3 _vanishingPoint;
};

#endif // __RayGenerator_h__