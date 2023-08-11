#include "Weapon.h"
#include "Framework/Components/RenderComponent.h"
#include "Framework/Components/CircleCollisionComponent.h"

void Weapon::Update(float dt) {
	Actor::Update(dt);
	antares::vec2 forward = antares::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * antares::g_time.getDeltaTime();

	m_destroyed = ((m_transform.position.x > antares::g_renderer.GetWidth() || m_transform.position.x < 0) || (m_transform.position.y > antares::g_renderer.GetHeight() || m_transform.position.y < 0));
}

bool Weapon::Initialize() {
	auto sComponent = GetComponent<antares::RenderComponent>();
	auto cComponent = GetComponent<antares::CircleCollisionComponent>();
	if (cComponent && sComponent) {
		cComponent->m_radius = sComponent->GetRadius() * m_transform.scale;
	}
	return true;
}

void Weapon::OnCollision(Actor* other) {
	if ((m_tag == "EnemyBullet" && other->m_tag == "Player") || (m_tag == "PlayerBullet" && other->m_tag == "Enemy")) {
		m_destroyed = true;
	}
}
