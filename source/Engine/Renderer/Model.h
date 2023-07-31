#pragma once
#include "Core/Core.h"
#include "Renderer.h"
#include <vector>

namespace antares {
	class Model {
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {};
		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const antares::Transform tf);
		bool Load(const std::string& filename);

		float GetRadius();

	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;
	};
}