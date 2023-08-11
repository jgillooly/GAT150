#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Weapon.h"
#include <memory>
#include "Renderer/ModelManager.h"
#include "SpaceGame.h"
#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Components/CircleCollisionComponent.h"
#include "Framework/Components/RenderComponent.h"

bool Enemy::Initialize() {
	auto sComponent = GetComponent<antares::RenderComponent>();
	auto cComponent = GetComponent<antares::CircleCollisionComponent>();
	if (cComponent && sComponent) {
		cComponent->m_radius = sComponent->GetRadius() * m_transform.scale;
	}
	return true;
}

void Enemy::Update(float dt) {
	Actor::Update(dt);

	Player* p = m_scene->GetActor<Player>();

	if (p) {
		antares::Vector2 direction = p->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + antares::HalfPi;

	}

	antares::vec2 forward = antares::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * antares::g_time.getDeltaTime();

	m_transform.position.x = antares::Wrap(m_transform.position.x, (float)antares::g_renderer.GetWidth());
	m_transform.position.y = antares::Wrap(m_transform.position.y, (float)antares::g_renderer.GetHeight());

	m_firetimer -= dt;
	if (m_firetimer <= 0) {
		antares::Transform transform2 {m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, 0.0f, transform2);
		weapon->m_tag = "EnemyBullet";
		m_scene->Add(std::move(weapon));
		if (m_special) {
			for (int i = 1; i <= 3; i++) {
				transform2 = { m_transform.position, m_transform.rotation + (antares::HalfPi * i), 1.0f };
				std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, 0.0f, transform2);
				weapon->m_tag = "EnemyBullet";
				m_scene->Add(std::move(weapon));
			}
		}
		m_firetimer = m_firetime;
	}
}

void Enemy::OnCollision(Actor* other) {
	if (other->m_tag == "PlayerBullet" && !m_destroyed) {
		m_destroyed = true;
		m_game->AddPoints(50);
		//antares::EmitterData data;
		//data.burst = true;
		//data.burstCount = 100;
		//data.spawnRate = 200;
		//data.angle = 0.0f;
		//data.angleRange = antares::Pi;
		//data.lifetimeMin = 0.5f;
		//data.lifetimeMax = 1.5f;
		//data.speedMin = 50;
		//data.speedMax = 250;
		//data.damping = 0.5f;
		//data.color = antares::Color{ 1.0f, 0.0f, 0.0f, 1.0f };
		//antares::Transform transform{ m_transform.position, 0.0f, 1.0f };
		//std::unique_ptr<antares::Emitter> emitter = std::make_unique<antares::Emitter>(transform, data);
		//emitter->m_lifespan = 1.0f;
		//emitter->m_tag = "Emitter";
		//m_scene->Add(std::move(emitter));
	}
}
