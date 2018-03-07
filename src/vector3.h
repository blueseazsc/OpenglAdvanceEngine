#ifndef VECTOR3_H
#define VECTOR3_H

#include "header.h"

namespace framework {
class Vector3f {
public:
	Vector3f(float vx = 0.f, float vy = 0.f, float vz = 0.f) : x(vx), y(vy), z(vz) {}
	Vector3f(const Vector3f& vec) : x(vec.x), y(vec.y), z(vec.z) {}
	const Vector3f& operator = (const Vector3f& vec) { x = vec.x; y = vec.y; z = vec.z; return *this; }

	const Vector3f& operator += (const Vector3f& vec) { x += vec.x; y += vec.y; z += vec.z; return *this; }
	const Vector3f& operator -= (const Vector3f& vec) { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
	const Vector3f& operator *= (float f) { x *= f; y *= f; z *= f; return *this; }
	const Vector3f& operator /= (float f) { f = 1.f / f; x *= f; y *= f; z *= f; return *this; }
	
	Vector3f operator + () const { return *this; }
	Vector3f operator - () const { return Vector3f(-x,-y,-z); }
	
	void clear() { x = y = z = 0.f; }

	float magnitude() const { return sqrt(x*x + y*y + z*z); }
	void normalize() {
		float len = magnitude();
		float f = 1.0f / len;
		x = x * f;
		y = y * f;
		z = z * f;
	}
public:
	float x, y, z;
};

bool operator == (const Vector3f& vec1, const Vector3f& vec2);
bool operator != (const Vector3f& vec1, const Vector3f& vec2);

Vector3f operator + (const Vector3f& vec1, const Vector3f& vec2);
Vector3f operator - (const Vector3f& vec1, const Vector3f& vec2);

Vector3f operator * (const Vector3f& vec, float f);
float operator * (const Vector3f& vec1, const Vector3f& vec2);

Vector3f operator / (const Vector3f& vec, float f);

Vector3f CrossProduct(const Vector3f& vec1, const Vector3f& vec2);
}
#endif
