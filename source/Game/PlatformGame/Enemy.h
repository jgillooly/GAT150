#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"
namespace antares {
	class Enemy : public antares::Actor {
	public:
		Enemy(float speed, float turnRate, const antares::Transform& transform) :
			Actor{ transform },
			speed{ speed }, jump{ jump } {
		}
		Enemy() = default;
		CLASS_DECLARATION(Enemy)

			bool Initialize() override;

		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;
	private:
		float speed = 0;
		float jump = 0;
		float maxSpeed = 0;
		int groundCount = 0;
		antares::PhysicsComponent* m_pComponent = nullptr;
	};
}