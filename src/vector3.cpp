#include "vector3.h"

namespace framework {

bool operator == (const Vector3f& vec1, const Vector3f& vec2) { return vec1.x==vec2.x && vec1.y==vec2.y && vec1.z==vec2.z; }
bool operator != (const Vector3f& vec1, const Vector3f& vec2) { return vec1.x!=vec2.x || vec1.y!=vec2.y || vec1.z!=vec2.z; }

Vector3f operator + (const Vector3f& vec1, const Vector3f& vec2) { return Vector3f(vec1.x+vec2.x, vec1.y+vec2.y, vec1.z+vec2.z); }
Vector3f operator - (const Vector3f& vec1, const Vector3f& vec2) { return Vector3f(vec1.x-vec2.x, vec1.y-vec2.y, vec1.z-vec2.z); }

Vector3f operator * (const Vector3f& vec, float f) { return Vector3f(vec.x*f, vec.y*f, vec.z*f); }
float operator * (const Vector3f& vec1, const Vector3f& vec2) { 
	return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}

Vector3f operator / (const Vector3f& vec, float f) { f = 1.f / f; return Vector3f(vec.x*f, vec.y*f, vec.z*f); }

Vector3f CrossProduct(const Vector3f& vec1, const Vector3f& vec2) {
	return Vector3f(vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x);
}

}
