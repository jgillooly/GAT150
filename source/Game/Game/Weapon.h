#pragma once
#include "Renderer/Model.h"
#include "Framework/Actor.h"
#include "Framework/Components/Component.h"
#include "Framework/Components/PhysicsComponent.h"
namespace antares {
	class Weapon : public Actor {
	public:
		CLASS_DECLARATION(Weapon);
		/*
		Weapon(float speed, float turnRate, const antares::Transform& transform) :
			Actor{ transform },
			m_speed{ speed }, m_turnRate{ turnRate } {
			lifespan = 2.0;
		}
		*/

		void Update(float dt) override;

		bool Initialize() override;

		void OnCollisionEnter(Actor* other);
	private:
		float speed = 0;
		float m_turnRate = 0;
		antares::PhysicsComponent* m_physicsComponent;
	};
}
