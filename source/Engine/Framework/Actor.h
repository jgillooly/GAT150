#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Framework/Game.h"
#include <memory>

namespace antares {
class Actor {
public:
	Actor() = default;
	Actor(const antares::Transform& transform, std::shared_ptr<Model> model) : m_transform{transform}, m_model {model} {}
	Actor(const antares::Transform& transform) :
		m_transform{ transform } {
	}

	virtual void Update(float dt);
	virtual void Draw(antares::Renderer& renderer);

	float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : -10000; }

	virtual void OnCollision(Actor* other) {}

	class Scene* m_scene = nullptr;
	Game* m_game = nullptr;
	friend class Scene;

	antares::Transform m_transform;

	std::string m_tag;
	inline bool isDestroyed() { return m_destroyed; }
protected:
	//antares::Model m_model;
	std::shared_ptr<Model> m_model;

	bool m_destroyed = false;
	float m_lifespan = -1.0f;
};
}