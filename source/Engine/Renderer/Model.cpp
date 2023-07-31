#include "Model.h"
#include "Core/FileIO.h"
#include <sstream>

namespace antares {
	void Model::Draw(Renderer& renderer, const vec2& pos, float rotation, float scale) {
		if (m_points.size() < 2) return;
		renderer.SetColor(Color::toInt(m_color.r), Color::toInt(m_color.g), Color::toInt(m_color.b), Color::toInt(m_color.a));
		for (int i = 0; i < m_points.size()-1; i++) {
			vec2 p1 = (m_points[i] * scale).Rotate(rotation) + pos;
			vec2 p2 = (m_points[i + 1] * scale).Rotate(rotation) + pos;

			renderer.DrawLine(p1.x,p1.y,p2.x,p2.y);
		}
	}

	void Model::Draw(Renderer& renderer, const antares::Transform tf) {
		Draw(renderer, tf.position, tf.rotation, tf.scale);
	}

	

	bool Model::Load(const std::string& filename) {
		std::string buffer;
		antares::readFile(filename, buffer);

		std::istringstream stream(buffer);
		//read color
		stream >> m_color;

		//read num points
		std::string line;
		std::getline(stream, line);

		int numPoints = std::stoi(line);

		//read points
		for (int i = 0; i < numPoints; i++) {
			Vector2 point;
			stream >> point;
			m_points.push_back(point);
			
		}

		return true;
	}

	float Model::GetRadius() {
		if (m_radius) return m_radius;
		for (auto point : m_points) {
			float length = point.Length();
			m_radius = Max(m_radius, length);
		}

		return m_radius;
	}
}