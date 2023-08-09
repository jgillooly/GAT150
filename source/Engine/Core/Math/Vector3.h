#pragma once
#pragma once
#include <cmath>
#include <istream>
#include <sstream>

namespace antares {
	class Vector3 {
	public:
		float x, y, z;
	public:
		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {};
		Vector3(float v) : x{ v }, y{ v }, z{ v } {};
		Vector3(float x, float y) : x{ x }, y{ y }, z{ 0 } {};
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z { z } {};
		Vector3(int x, int y) : x{ (float)x }, y{ (float)y }, z{ 0 } {}
		Vector3(int x, int y, int z) : x{ (float)x }, y{ (float)y }, z{ (float)z } {}

		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }

		Vector3 operator - () const { return { -x, -y, -z }; }

		//Vector3 Add(Vector3 v) { return Vector3(x + v.x, y + v.y); }
		Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
		Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
		Vector3 operator / (const Vector3& v) const { return Vector3(x / v.x, y / v.y, z / v.z); }
		Vector3 operator * (const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }

		Vector3 operator + (const float s) const { return Vector3(x + s, y + s, z + s); }
		Vector3 operator - (const float s) const { return Vector3(x - s, y - s, z - s); }
		Vector3 operator / (const float s) const { return Vector3(x / s, y / s, z / s); }
		Vector3 operator * (const float s) const { return Vector3(x * s, y * s, z * s); }

		Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x; y /= v.y; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x; y *= v.y; return *this; }

		float LengthSqr() const { return (x * x) + (y * y); }
		float Length() const { return std::sqrt(LengthSqr()); }

		float DistanceSqr(const Vector3& v) {
			return (*this - v).LengthSqr();
		}

		float Distance(const Vector3& v) {
			return (*this - v).Length();
		}

		Vector3 Normalized() const { return *this / Length(); }
		void Normalize() { *this /= Length(); }

		static float Dot(const Vector3& v1, const Vector3& v2);
	};


	using vec3 = Vector3;
}