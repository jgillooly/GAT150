#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace antares {
    CLASS_DEFINITION(CircleCollisionComponent)

    void CircleCollisionComponent::Update(float dt) {

    }

    bool CircleCollisionComponent::CheckCollision(CollisionComponent* other) {
        float distance = m_owner->m_transform.position.Distance(other->m_owner->m_transform.position);
        return (distance <= m_radius + other->m_radius);
    }
}