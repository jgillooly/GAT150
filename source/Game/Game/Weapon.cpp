#include "Weapon.h"
#include "Framework/Components/RenderComponent.h"
#include "Framework/Components/CircleCollisionComponent.h"
namespace antares {
	void Weapon::Read(const json_t& value) {
		READ_DATA(value, speed);
	}
	void Weapon::Update(float dt) {
		Actor::Update(dt);
		antares::vec2 forward = antares::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * antares::g_time.getDeltaTime();

	}

	bool Weapon::Initialize() {
		auto sComponent = GetComponent<antares::RenderComponent>();
		auto cComponent = GetComponent<antares::CircleCollisionComponent>();
		if (cComponent && sComponent) {
			cComponent->m_radius = sComponent->GetRadius() * transform.scale;
		}
		return true;
	}

	void Weapon::OnCollision(Actor* other) {
		if ((tag == "EnemyBullet" && other->tag == "Player") || (tag == "PlayerBullet" && other->tag == "Enemy")) {
			//m_owner->m_destroyed = true;
		}
	}
}
