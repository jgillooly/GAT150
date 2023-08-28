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
namespace antares {
	CLASS_DEFINITION(Player)
		bool Player::Initialize() {
		Actor::Initialize();
		m_pComponent = GetComponent<antares::PhysicsComponent>();
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
		antares::vec2 forward = antares::vec2{ 1,0 };
		antares::vec2 result = forward * 100 * dir;
		m_pComponent->ApplyForce(forward * 50 * dir);

		bool onGround = groundCount > 0;
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !antares::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			antares::vec2 up = { 0.0, 50.0f };
			m_pComponent->ApplyForce(up);
		}
	}

	void Player::OnCollisionEnter(Actor* other) {
		if (other->tag == "Ground") {
			groundCount++;
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
	}
}