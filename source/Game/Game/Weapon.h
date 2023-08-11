#pragma once
#include "Renderer/Model.h"
#include "Framework/Actor.h"
	class Weapon : public antares::Actor {
	public:
		Weapon(float speed, float turnRate, const antares::Transform& transform) :
			Actor{ transform },
			m_speed{ speed }, m_turnRate{ turnRate } {
			m_lifespan = 2.0;
		}
		void Update(float dt) override;

		bool Initialize() override;

		void OnCollision(Actor* other) override;
	private:
		float m_speed = 0;
		float m_turnRate = 0;
	};
