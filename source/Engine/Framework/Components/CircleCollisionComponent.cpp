#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace antares {
    CLASS_DEFINITION(CircleCollisionComponent)

    void CircleCollisionComponent::Update(float dt) {

    }

    bool CircleCollisionComponent::CheckCollision(CollisionComponent* other) {
        float distance = m_owner->transform.position.Distance(other->m_owner->transform.position);
        return (distance <= m_radius + other->m_radius);
    }

    void CircleCollisionComponent::Read(const json_t& value) {

    }
}