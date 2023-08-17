#pragma once
#include "Renderer/Model.h"
#include "Framework/Actor.h"
#include "Framework/Components/Component.h"
namespace antares {
	class Weapon : public Actor {
	public:
		/*
		Weapon(float speed, float turnRate, const antares::Transform& transform) :
			Actor{ transform },
			m_speed{ speed }, m_turnRate{ turnRate } {
			lifespan = 2.0;
		}
		*/

		void Read(const json_t& value);

		void Update(float dt) override;

		bool Initialize() override;

		void OnCollision(Actor* other);
	private:
		float speed = 0;
		float m_turnRate = 0;
	};
}
