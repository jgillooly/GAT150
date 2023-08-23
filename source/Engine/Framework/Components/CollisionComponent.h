#pragma once
#include "Component.h"
namespace antares {
	class CollisionComponent : public Component {
	public:
		virtual bool CheckCollision(CollisionComponent* other) { return true; };
	public:
		float m_radius = 0;
	};
}