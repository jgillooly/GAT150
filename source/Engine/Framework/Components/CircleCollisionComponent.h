#pragma once
#include "CollisionComponent.h"
namespace antares {
	class CircleCollisionComponent : public CollisionComponent {
	public:
		// Inherited via CollisionComponent
		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* other) override;
	};
}