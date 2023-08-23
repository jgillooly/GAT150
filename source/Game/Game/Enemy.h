#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>
#include "Framework/Components/PhysicsComponent.h"

namespace antares {
class Enemy : public antares::Actor {
public:
	Enemy(float speed, float turnRate, const antares::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }, m_turnRate{ turnRate }, m_special{ false } {
		m_firetime = 2.0f;
		m_firetimer = antares::randomf(0.0f, m_firetime);
	}
	bool Initialize() override;
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:
	bool m_special = false;
	float m_speed = 0;
	float m_turnRate = 0;

	float m_firetime = 0;
	float m_firetimer = 0;
	antares::PhysicsComponent* m_physicsComponent;
};
}