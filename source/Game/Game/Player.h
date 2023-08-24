#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/EnginePhysicsComponent.h"
namespace antares {
	class Player : public antares::Actor {
	public:
		Player(float speed, float turnRate, const antares::Transform& transform) :
			Actor{ transform },
			speed{ speed }, turnRate{ turnRate } {
			m_boostSpeed = speed * 2;
		}
		Player() = default;
		CLASS_DECLARATION(Player)

		bool Initialize() override;

		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		bool canBoost() { return m_boostTimer >= m_boostTime; }
		std::string getBoostStatus();
	private:
		float speed = 0;
		float m_boostSpeed;
		float turnRate = 0;
		float m_health = 200;
		float m_boostTime = 5;
		float m_boostTimer = 5;
		float m_boostActiveTime = 2;
		float m_boostActiveTimer = 0;
		bool m_boosting = false;

		antares::PhysicsComponent* m_pComponent = nullptr;
	};
}