#include "Actor.h"
#include "Components/RenderComponent.h"
#include "rapidjson/include/rapidjson/rapidjson.h"
namespace antares {
	CLASS_DEFINITION(Actor)
	bool Actor::Initialize() {
		for (auto& component : components) {
			component->Initialize();
		}
		return true;
	}

	void Actor::OnDestroy() {
		for (auto& component : components) {
			component->OnDestroy();
		}
	}

	void Actor::Update(float dt) {
		if (lifespan != -1.0f) {
			lifespan -= dt;
			m_destroyed = (lifespan <= 0);
		}

		for (auto& component : components) {
			component->Update(dt);
		}
	}
	void Actor::Draw(antares::Renderer& renderer) {
		for (auto& component : components) {
			RenderComponent* renderable = dynamic_cast<RenderComponent*>(component.get());
			if (renderable) {
				renderable->Draw(renderer);
			}
		}
	}
	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->m_owner = this;
		components.push_back(std::move(component));
	}

	void Actor::Read(const json_t& value) {
		//Read name
		Object::Read(value);
		//Read tag
		READ_DATA(value, tag);
		//Read transform
		if (HAS_DATA(value, transform)) transform.Read(GET_DATA(value, transform));
		//Read Lifespan
		READ_DATA(value, lifespan);
		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray()) {
			for (auto& componentValue : GET_DATA(value, components).GetArray()) {
				std::string type;
				READ_DATA(componentValue, type);
				auto component = CREATE_CLASS_BASE(Component, type);
				component->Read(componentValue);

				AddComponent(std::move(component));
			}
		}
	}
}
