#include "Weapon.h"
#include "Framework/Components/RenderComponent.h"
#include "Framework/Components/CircleCollisionComponent.h"
namespace antares {
	CLASS_DEFINITION(Weapon);
	void Weapon::Read(const json_t& value) {
		Actor::Read(value);
		READ_DATA(value, speed);
	}
	void Weapon::Update(float dt) {
		Actor::Update(dt);
		antares::vec2 forward = antares::vec2{ 0, -1 }.Rotate(transform.rotation);
		m_physicsComponent->SetVelocity(forward * speed);

	}

	bool Weapon::Initialize() {
		Actor::Initialize();
		auto sComponent = GetComponent<antares::RenderComponent>();
		auto cComponent = GetComponent<antares::CircleCollisionComponent>();
		m_physicsComponent = GetComponent<PhysicsComponent>();
		if (cComponent && sComponent) {
			cComponent->m_radius = sComponent->GetRadius() * transform.scale;
		}
		return true;
	}

	void Weapon::OnCollisionEnter(Actor* other) {
		if ((tag == "EnemyBullet" && other->tag == "Player") || (tag == "PlayerBullet" && other->tag == "Enemy")) {
			//m_owner->m_destroyed = true;
		}
	}
}
