#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Weapon.h"
//#include <memory>
#include "Renderer/ModelManager.h"
#include "SpaceGame.h"
#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Components/CircleCollisionComponent.h"
#include "Framework/Components/RenderComponent.h"
namespace antares {
	CLASS_DEFINITION(Enemy)
	bool Enemy::Initialize() {
		Actor::Initialize();
		m_physicsComponent = GetComponent<antares::PhysicsComponent>();
		auto sComponent = GetComponent<antares::RenderComponent>();
		auto cComponent = GetComponent<antares::CircleCollisionComponent>();
		if (cComponent && sComponent) {
			cComponent->m_radius = sComponent->GetRadius() * transform.scale;
		}
		return true;
	}

	void Enemy::Update(float dt) {
		Actor::Update(dt);

		Player* p = m_scene->GetActor<Player>();

		if (p) {
			antares::Vector2 direction = p->transform.position - transform.position;
			

		}

		antares::vec2 forward = antares::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * antares::g_time.getDeltaTime();

		m_physicsComponent->ApplyForce(forward * speed);

		transform.position.x = antares::Wrap(transform.position.x, (float)antares::g_renderer.GetWidth());
		transform.position.y = antares::Wrap(transform.position.y, (float)antares::g_renderer.GetHeight());

		//m_firetimer -= dt;
		//if (m_firetimer <= 0) {
		//	antares::Transform transform2 {transform.position, transform.rotation, 1};
		//	std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, 0.0f, transform2);
		//	weapon->tag = "EnemyBullet";
		//	m_scene->Add(std::move(weapon));
		//	if (m_special) {
		//		for (int i = 1; i <= 3; i++) {
		//			transform2 = { transform.position, transform.rotation + (antares::HalfPi * i), 1.0f };
		//			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, 0.0f, transform2);
		//			weapon->tag = "EnemyBullet";
		//			m_scene->Add(std::move(weapon));
		//		}
		//	}
		//	m_firetimer = m_firetime;
		//}
	}

	void Enemy::OnCollisionEnter(Actor* other) {
		if (other->tag == "PlayerBullet" && !m_destroyed) {
			antares::EventManager::Instance().DispatchEvent("AddPoints", 100);
			m_destroyed = true;
			//m_game->AddPoints(50);
			antares::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0.0f;
			data.angleRange = antares::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMax = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = antares::Color{ 1.0f, 0.0f, 0.0f, 1.0f };
			antares::Transform transform1{ transform.position, 0.0f, 1.0f };
			std::unique_ptr<antares::Emitter> emitter = std::make_unique<antares::Emitter>(transform1, data);
			emitter->lifespan = 1.0f;
			emitter->tag = "Emitter";
			m_scene->Add(std::move(emitter));
		}
	}

	void Enemy::Read(const json_t& value) {
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}
}
