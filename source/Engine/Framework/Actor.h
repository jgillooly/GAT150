#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Framework/Game.h"
#include "Components/Component.h"
#include "Object.h"
#include <memory>

namespace antares {
class Actor : public Object {
public:
	CLASS_DECLARATION(Actor)
	Actor() = default;
	Actor(const antares::Transform& transform, std::shared_ptr<Model> model) : transform{transform} {}
	Actor(const antares::Transform& transform) :
		transform{ transform } {
	}

	virtual bool Initialize() override;
	virtual void OnDestroy() override;

	virtual void Update(float dt);
	virtual void Draw(antares::Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);

	float GetRadius() { return 30.0f; }

	virtual void OnCollision(Actor* other) {}

	class Scene* m_scene = nullptr;
	Game* m_game = nullptr;
	friend class Scene;

	antares::Transform transform;

	std::string tag;
	inline bool isDestroyed() { return m_destroyed; }
	friend class SpaceGame;
	template<typename T>
	T* GetComponent();
protected:
	std::vector<std::shared_ptr<Component>> components;
	//antares::Model m_model;

	bool m_destroyed = false;
	float lifespan = -1.0f;
};
template<typename T>
inline T* Actor::GetComponent() {
	for (auto& component : components) {
		T* result = dynamic_cast<T*>(component.get());
		if (result) return result;
	}

	return nullptr;
}
}