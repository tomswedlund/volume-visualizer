#include <cfloat>
#include <cmath>
#include <cstring>
#include <exception>
#include "Matrix3x3.h"
#include "Vector3.h"
#include "Utils.h"

namespace {
	float det2x2(float a, float b, float c, float d) {
		return (a * d - b * c);
	}
}

Matrix3x3 Matrix3x3::identity() {
	Matrix3x3 temp;
	temp(0, 0) = 1;
	temp(1, 1) = 1;
	temp(2, 2) = 1;
	return temp;
}

Matrix3x3::Matrix3x3()
{
	memset(this->_elements, 0, sizeof(float)* 9);
}

Matrix3x3::Matrix3x3(const Matrix3x3& toCopy) {
	Matrix3x3::copy(toCopy, *this);
}

Matrix3x3::~Matrix3x3() {
}

Matrix3x3 Matrix3x3::inverse() const {
	Matrix3x3 inverse;
	const Matrix3x3& matrix = *this;

	// Calc minors.
	float minor1 = det2x2(matrix(1, 1), matrix(1, 2), matrix(2, 1), matrix(2, 2));
	float minor2 = det2x2(matrix(1, 0), matrix(1, 2), matrix(2, 0), matrix(2, 2));
	float minor3 = det2x2(matrix(1, 0), matrix(1, 1), matrix(2, 0), matrix(2, 1));
	inverse(0, 0) = minor1;
	inverse(0, 1) = minor2;
	inverse(0, 2) = minor3;
	inverse(1, 0) = det2x2(matrix(0, 1), matrix(0, 2), matrix(2, 1), matrix(2, 2));
	inverse(1, 1) = det2x2(matrix(0, 0), matrix(0, 2), matrix(2, 0), matrix(2, 2));
	inverse(1, 2) = det2x2(matrix(0, 0), matrix(0, 1), matrix(2, 0), matrix(2, 1));
	inverse(2, 0) = det2x2(matrix(0, 1), matrix(0, 2), matrix(1, 1), matrix(1, 2));
	inverse(2, 1) = det2x2(matrix(0, 0), matrix(0, 2), matrix(1, 0), matrix(1, 2));
	inverse(2, 2) = det2x2(matrix(0, 0), matrix(0, 1), matrix(1, 0), matrix(1, 1));

	// Calc cofactors.
	inverse(0, 1) = -inverse(0, 1);
	inverse(1, 0) = -inverse(1, 0);
	inverse(1, 2) = -inverse(1, 2);
	inverse(2, 1) = -inverse(2, 1);

	// Calc determinant.
	float det = matrix(0, 0) * minor1 - matrix(0, 1) * minor2 + matrix(0, 2) * minor3;

	// Inverse!
	return inverse.transpose() / det;
}

Matrix3x3 Matrix3x3::transpose() const {
	Matrix3x3 temp;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			temp._elements[i][j] = this->_elements[j][i];
		}
	}
	return temp;
}

Matrix3x3& Matrix3x3::operator =(const Matrix3x3& rhs) {
	Matrix3x3::copy(rhs, *this);
	return *this;
}

float& Matrix3x3::operator ()(int row, int col) {
	return this->_elements[row][col];
}
float Matrix3x3::operator ()(int row, int col) const {
	return this->_elements[row][col];
}

Matrix3x3& Matrix3x3::operator +=(const Matrix3x3& rhs) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			this->_elements[i][j] += rhs._elements[i][j];
		}
	}
	return *this;
}

Matrix3x3& Matrix3x3::operator -=(const Matrix3x3& rhs) {
	*this += -rhs;
	return *this;
}

Matrix3x3& Matrix3x3::operator *=(const Matrix3x3& rhs) {
	Matrix3x3 result;
	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < 3; ++col) {
			float temp = 0;
			for (int el = 0; el < 3; ++el) {
				temp += (this->_elements[row][el] * rhs._elements[el][col]);
			}
			result._elements[row][col] = temp;
		}
	}
	*this = result;
	return *this;
}

Matrix3x3& Matrix3x3::operator *=(float scalar) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			this->_elements[i][j] *= scalar;
		}
	}
	return *this;
}

Matrix3x3& Matrix3x3::operator /=(float scalar) {
	*this *= (1.0f / scalar);
	return *this;
}

Matrix3x3 Matrix3x3::operator +(const Matrix3x3& rhs) const {
	Matrix3x3 temp(*this);
	temp += rhs;
	return temp;
}

Matrix3x3 Matrix3x3::operator -(const Matrix3x3& rhs) const {
	Matrix3x3 temp(*this);
	temp -= rhs;
	return temp;
}

Matrix3x3 Matrix3x3::operator *(const Matrix3x3& rhs) const {
	Matrix3x3 temp(*this);
	temp *= rhs;
	return temp;
}

Vector3 Matrix3x3::operator *(const Vector3& rhs) const {
	Vector3 temp;
	temp.x(this->_elements[0][0] * rhs.x() +
		this->_elements[0][1] * rhs.y() +
		this->_elements[0][2] * rhs.z());
	temp.y(this->_elements[1][0] * rhs.x() +
		this->_elements[1][1] * rhs.y() +
		this->_elements[1][2] * rhs.z());
	temp.z(this->_elements[2][0] * rhs.x() +
		this->_elements[2][1] * rhs.y() +
		this->_elements[2][2] * rhs.z());
	return temp;
}

Matrix3x3 Matrix3x3::operator *(float scalar) const {
	Matrix3x3 temp(*this);
	temp *= scalar;
	return temp;
}

Matrix3x3 Matrix3x3::operator /(float scalar) const {
	Matrix3x3 temp(*this);
	temp /= scalar;
	return temp;
}

Matrix3x3 Matrix3x3::operator -() const {
	Matrix3x3 temp;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			temp._elements[i][j] = -this->_elements[i][j];
		}
	}
	return temp;
}

void Matrix3x3::copy(const Matrix3x3& from, Matrix3x3& to) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			to._elements[i][j] = from._elements[i][j];
		}
	}
}