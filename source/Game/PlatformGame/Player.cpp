#include "Player.h"
#include "../../Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Renderer/ModelManager.h"
#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/EnginePhysicsComponent.h"
#include "Framework/Components/CircleCollisionComponent.h"
#include "Framework/Event/EventManager.h"
#include "Framework/Components/SpriteAnimRenderComponent.h"
#include "Audio/AudioSystem.h"
#include "PlatformGame.h"
namespace antares {
	CLASS_DEFINITION(Player)
		bool Player::Initialize() {

		Actor::Initialize();
		
		m_pComponent = GetComponent<antares::PhysicsComponent>();
		m_sComponent = GetComponent<SpriteAnimRenderComponent>();

		return true;
	}

	void Player::Update(float dt) {
		Actor::Update(dt);


		m_pComponent->Update(dt);


		float dir = 0;
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) {
			dir = 1;
		}
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) {
			dir = -1;
		}
		vec2 velocity = m_pComponent->m_velocity;
		antares::vec2 forward = antares::vec2{ 1,0 };
		antares::vec2 result = forward * 100 * dir;
		bool onGround = groundCount > 0;
		if (dir) {
			//m_pComponent->ApplyForce(forward * 50 * dir);
			velocity.x += speed * dir * ((onGround) ? 1 : 0.25f);
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_pComponent->SetVelocity(velocity);
		}

		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !antares::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE) && jumps > 0) {
			antares::vec2 up = { 0.0, -1.0f };
			m_pComponent->SetVelocity(velocity + (up * jump));
			jumps--;
			antares::g_audioSystem.PlayOneShot("jump");
		}

		//m_pComponent->SetGravityScale((velocity.y > 0) ? 3.0f : 2.0f);

		//animation
		if (std::fabs(velocity.x) > 0.2) {
			if (dir != 0) m_sComponent->flipH = (dir < 0);
			m_sComponent->SetSequence("run");
		}
		else {
			m_sComponent->SetSequence("idle");
		}
	}

	void Player::OnCollisionEnter(Actor* other) {
		if (other->tag == "Ground") {
			groundCount++;
			if (other->transform.position.y > transform.position.y) jumps = 2;
		}
		else if (other->tag == "Enemy" && other->transform.position.y < transform.position.y) {
			m_destroyed = true;
			EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}
		else if (other->tag == "Coin") {
			other->m_destroyed = true;
			EventManager::Instance().DispatchEvent("AddPoints", 100);
		}
	}

	void Player::OnCollisionExit(Actor* other) {
		if (other->tag == "Ground") {
			groundCount--;
		}
	}


	void Player::Read(const json_t& value) {
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);
		READ_DATA(value, maxSpeed);
	}
}