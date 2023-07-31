#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>
class Enemy : public antares::Actor {
public:
	Enemy(float speed, float turnRate, const antares::Transform& transform, std::shared_ptr<antares::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }, m_turnRate{ turnRate } {
		m_firetime = 2.0f;
		m_firetimer = antares::randomf(0.0f, m_firetime);
	}
	Enemy(float speed, float turnRate, const antares::Transform& transform, std::shared_ptr<antares::Model> model, bool special) :
		Actor{ transform, model },
		m_speed{ speed }, m_turnRate{ turnRate }, m_special{ special } {
		m_firetime = 2.0f;
		m_firetimer = antares::randomf(0.0f, m_firetime);
	}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:
	bool m_special = false;
	float m_speed = 0;
	float m_turnRate = 0;
	
	float m_firetime = 0;
	float m_firetimer = 0;
};