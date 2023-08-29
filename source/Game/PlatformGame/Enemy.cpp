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
		antares::vec2 direction = p->transform.position - transform.position;
		m_pComponent->ApplyForce(direction.Normalized() * speed);
	}

	void Enemy::OnCollisionEnter(Actor* other) {
		
	}

	void Enemy::OnCollisionExit(Actor* other) {
	}

	void Enemy::Read(const json_t& value) {
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}
