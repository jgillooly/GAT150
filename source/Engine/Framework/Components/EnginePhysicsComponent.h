#pragma once
#include "PhysicsComponent.h"
#include "Framework/Factory.h"
namespace antares {
	class EnginePhysicsComponent : public PhysicsComponent {
	public:
		CLASS_DECLARATION(EnginePhysicsComponent)
		// Inherited via PhysicsComponent
		virtual void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;

		// Inherited via PhysicsComponent
		void ApplyTorque(float torque) override;
	};
}