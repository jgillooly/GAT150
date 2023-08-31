#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
//#include <memory>
#include "Renderer/ModelManager.h"

#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Components/CircleCollisionComponent.h"
#include "Framework/Components/RenderComponent.h"
#include "Framework/Event/EventManager.h"
namespace antares {
	CLASS_DEFINITION(Enemy)
	bool Enemy::Initialize() {
		Actor::Initialize();
		m_pComponent = GetComponent<antares::PhysicsComponent>();
		return true;
	}

	void Enemy::Update(float dt) {
		Actor::Update(dt);

		Player* p = m_scene->GetActor<Player>();
		if (p) {
			antares::vec2 direction = p->transform.position - transform.position;
			direction.Normalize();
			direction *= speed;
			direction.x = Clamp(direction.x, -maxSpeed, maxSpeed);
			direction.y = Clamp(direction.y, -maxSpeed, maxSpeed);


			m_pComponent->SetVelocity(direction);
		}
	}

	void Enemy::OnCollisionEnter(Actor* other) {
		if (other->tag == "Player" && other->transform.position.y < transform.position.y) {
			m_destroyed = true;
			EventManager::Instance().DispatchEvent("AddPoints", 100);
		}
	}

	void Enemy::OnCollisionExit(Actor* other) {
	}

	void Enemy::Read(const json_t& value) {
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);
		READ_DATA(value, maxSpeed);
	}
}
