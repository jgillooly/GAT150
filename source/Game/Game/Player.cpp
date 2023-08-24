#include "Player.h"
#include "../../Input/InputSystem.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Renderer/ModelManager.h"
#include "SpaceGame.h"
#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/EnginePhysicsComponent.h"
#include "Framework/Components/CircleCollisionComponent.h"
#include "Framework/Event/EventManager.h"
namespace antares {
	CLASS_DEFINITION(Player)
	bool Player::Initialize() {
		Actor::Initialize();
		m_pComponent = GetComponent<antares::PhysicsComponent>();
		auto sComponent = GetComponent<antares::RenderComponent>();
		auto cComponent = GetComponent<antares::CircleCollisionComponent>();
		if (cComponent && sComponent) {
			cComponent->m_radius = sComponent->GetRadius() * transform.scale;
		}
		return true;
	}

	void Player::Update(float dt) {
		Actor::Update(dt);

		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !antares::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			//	antares::Transform transform2 {transform.position, transform.rotation, 1};
			//	std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, 0.0f, transform2);
			//	weapon->tag = "PlayerBullet";
			//	std::unique_ptr<antares::SpriteComponent> component = std::make_unique<antares::SpriteComponent>();
			//	component->m_texture = GET_RESOURCE(antares::Texture, "Rocket.png", antares::g_renderer);
			//	weapon->AddComponent(std::move(component));
			//	auto eCComponent = std::make_unique <antares::CircleCollisionComponent>();
			//	eCComponent->m_radius = 30.0f;
			//	weapon->AddComponent(std::move(eCComponent));
			//	weapon->Initialize();
			//	m_scene->Add(std::move(weapon));
			auto weapon = INSTANTIATE(Weapon, "Rocket");
			weapon->transform = { transform.position, transform.rotation, 1 };
			weapon->tag = "PlayerBullet";
			weapon->Initialize();
			m_scene->Add(std::move(weapon));

		}

		m_pComponent->Update(dt);

		float rotate = 0;
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		//transform.rotation += rotate * m_turnRate * antares::g_time.getDeltaTime();
		m_pComponent->ApplyTorque(rotate * turnRate);

		if (m_boosting) {
			m_boostActiveTimer += dt;
			if (m_boostActiveTimer >= m_boostActiveTime) {
				m_boosting = false;
				m_boostActiveTimer = 0;
			}
		}
		else {
			m_boostTimer += dt;
		}

		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_LSHIFT) && !m_boosting && canBoost()) {
			m_boosting = true;
			m_boostTimer = 0;
		}



		float thrust = 0;
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;
		antares::vec2 forward = antares::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * (m_boosting ? m_boostSpeed : speed) * antares::g_time.getDeltaTime() * thrust;
		//m_pComponent->ApplyForce(forward * (m_boosting ? m_boostSpeed : m_speed) * thrust);

		antares::vec2 direction;
		//m_transform.position += (direction.Rotate(m_transform.rotation) * m_speed * antares::g_time.getDeltaTime());
		transform.position.x = antares::Wrap(transform.position.x, (float)antares::g_renderer.GetWidth());
		transform.position.y = antares::Wrap(transform.position.y, (float)antares::g_renderer.GetHeight());
	}

	void Player::OnCollisionEnter(Actor* other) {
		if (other->tag == "EnemyBullet" && !other->isDestroyed() && !m_destroyed) {
			std::cout << "Boom";
			//m_game->SetLives(m_game->GetLives() - 1);
			//dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::PlayerDead);
			antares::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
			m_destroyed = true;
			if (m_destroyed) {
				antares::EmitterData data;
				data.burst = true;
				data.burstCount = 100;
				data.spawnRate = 200;
				data.angle = 0;
				data.angleRange = antares::Pi;
				data.lifetimeMin = 0.5f;
				data.lifetimeMax = 1.5f;
				data.speedMin = 50;
				data.speedMax = 250;
				data.damping = 0.5f;
				data.color = antares::Color{ 1, 0, 0, 1 };
				antares::Transform transform{ transform.position, 0, 1 };
				auto emitter = std::make_unique<antares::Emitter>(transform, data);
				emitter->lifespan = 1.0f;
				emitter->tag = "Emitter";
				m_scene->Add(std::move(emitter));
			}
		}
	}

	std::string Player::getBoostStatus() {
		if (m_boosting) return "Boosting";
		if (canBoost()) return "Boost Ready";
		return "Boost Recharging";
	}

	void Player::Read(const json_t& value) {
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}
}