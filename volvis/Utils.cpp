#include <cmath>
#include <cstdlib>
#include "Matrix3x3.h"
#include "Transform.h"
#include "Utils.h"
#include "Vector3.h"

namespace {
	const float PI = 3.1415926535897932384626433832795f;
	const float EQUALS_THRESHOLD = 0.001f;
}

float Utils::deg2rad(float angle) {
	return (angle * PI / 180.0f);
}

Matrix3x3 Utils::createRotateMatrix(float angle, const Vector3& aboutVec) {
	float xy = aboutVec.x() * aboutVec.y();
	float xz = aboutVec.x() * aboutVec.z();
	float yz = aboutVec.y() * aboutVec.z();
	float rads = Utils::deg2rad(angle);
	float cos = cosf(rads);
	float sin = sinf(rads);
	float omc = 1 - cos;
	float oms = 1 - sin;

	Matrix3x3 rotMat;
	rotMat(0, 0) = cos + aboutVec.x() * aboutVec.x() * omc;
	rotMat(0, 1) = xy * omc - aboutVec.z() * sin;
	rotMat(0, 2) = xz * omc + aboutVec.y() * sin;
	rotMat(1, 0) = xy * omc + aboutVec.z() * sin;
	rotMat(1, 1) = cos + aboutVec.y() * aboutVec.y() * omc;
	rotMat(1, 2) = yz * omc - aboutVec.x() * sin;
	rotMat(2, 0) = xz * omc - aboutVec.y() * sin;
	rotMat(2, 1) = yz * omc + aboutVec.x() * sin;
	rotMat(2, 2) = cos + aboutVec.z() * aboutVec.z() * omc;
	return rotMat;
}

bool Utils::equals(float value, float compare) {
	float dist = value - compare;
	return (abs(dist) <= EQUALS_THRESHOLD);
}

Vector3 Utils::normalTransform(const Vector3& normal, const Transform& transform) {
	return transform.matrix().inverse().transpose() * normal;
}

float Utils::jitter(float t, float step) {
	return (rand() / (float)RAND_MAX) * step + t;
}

void Utils::transformImageCoords(int imageWidth, int imageHeight, int x, int y, float& imageX, float& imageY) {
	static const float halfWidth = 0.5f;

	float aspectRatio = imageHeight / (float)imageWidth;
	imageX = x / (float)imageWidth - halfWidth;
	imageY = (y / (float)imageHeight * aspectRatio) - (aspectRatio / 2);
}