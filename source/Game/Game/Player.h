#pragma once
#include "Framework/Actor.h"
class Player : public antares::Actor {
public:
	Player(float speed, float turnRate, const antares::Transform& transform, std::shared_ptr<antares::Model> model) :
		Actor{ transform, model },
		m_speed{speed}, m_turnRate{turnRate}
	{
		m_boostSpeed = m_speed * 2;
	}
	void Update(float dt) override;

	void OnCollision(Actor* other) override;
	bool canBoost() { return m_boostTimer >= m_boostTime; }
	std::string getBoostStatus();
private:
	float m_speed = 0;
	float m_boostSpeed;
	float m_turnRate = 0;
	float m_health = 200;
	float m_boostTime = 5;
	float m_boostTimer = 5;
	float m_boostActiveTime = 2;
	float m_boostActiveTimer = 0;
	bool m_boosting = false;
};