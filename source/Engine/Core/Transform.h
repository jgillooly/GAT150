#pragma once
#include "Vector2.h"
#include "Math/Matrix33.h"
#include "Json.h"

namespace antares {
	class Transform {
	public:
		vec2 position;
		float rotation= 0;
		float scale = 1;

	public:
		Transform() = default;
		Transform (const vec2& position, float rotation, float scale = 1) : position {position}, rotation {rotation}, scale {scale} {}

		mat3 GetMatrix() const {
			mat3 ms = Matrix33::CreateScale(scale);
			mat3 mr = Matrix33::CreateRotation(rotation);
			mat3 mt = Matrix33::CreateTranslation(position);

			return ( mt * ms * mr );
		}


		void Read(const json_t& value);
	};
}