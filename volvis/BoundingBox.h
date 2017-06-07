#ifndef __BoundingBox_h__
#define __BoundingBox_h__

class Ray;

class BoundingBox {
public:
	BoundingBox(float width, float height, float depth);
	BoundingBox(const BoundingBox& toCopy);
	~BoundingBox();
	BoundingBox& operator =(const BoundingBox& rhs);

	bool intersect(const Ray& ray, float& tIn, float& tOut) const;
	
	float width() const;
	float height() const;
	float depth() const;

private:
	static void copy(const BoundingBox& from, BoundingBox& to);

	float _width, _height, _depth;
};

#endif // __BoundingBox_h__