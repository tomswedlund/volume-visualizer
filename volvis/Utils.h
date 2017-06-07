#ifndef __Utils_h__
#define __Utils_h__

class Matrix3x3;
class Transform;
class Vector3;

class Utils {
public:
	static float deg2rad(float angle);
	static Matrix3x3 createRotateMatrix(float angle, const Vector3& aboutVec);
	static bool equals(float value, float compare);
	static Vector3 normalTransform(const Vector3& normal, const Transform& transform);
	static float jitter(float t, float step);
	static void transformImageCoords(int imageWidth, int imageHeight, int x, int y, float& imageX, float& imageY);

	template<typename T>
	static void minMax(T& min, T& max) {
		if (min > max) {
			T temp = max;
			max = min;
			min = temp;
		}
	}

	template<typename T>
	static void clamp(T& value) {
		if (value > 1) {
			value = 1;
		}
		else if (value < 0) {
			value = 0;
		}
	}
};

#endif // __Utils_h__