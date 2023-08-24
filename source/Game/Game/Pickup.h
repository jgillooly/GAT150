#pragma once
#include "Framework/Actor.h"

class Pickup : public antares::Actor {
public:
	Pickup(const antares::Transform& transform, std::shared_ptr<antares::Model> model, float lifespan) :
		Actor{ transform, model },
		m_speed{ 0 }, m_turnRate{ 0 }, m_lifespan {lifespan} {}
	void Update(float dt) override;

	void OnCollisionEnter(Actor* other) override;
private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_life = 0;
	float m_lifespan = 0;
};