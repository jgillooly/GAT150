#pragma once
#include "Vector2.h"
#include "Math/Matrix22.h"

namespace antares {
	class Transform {
	public:
		vec2 position;
		float rotation= 0;
		float scale = 1;

	public:
		Transform() = default;
		Transform (const vec2& position, float rotation, float scale = 1) : position {position}, rotation {rotation}, scale {scale} {}

		mat2 GetMatrix() const {
			mat2 ms = Matrix22::CreateScale(scale);
			mat2 mr = Matrix22::CreateRotation(rotation);

			return ( ms * mr );
		}
	};
}