#pragma once
#include <list>
#include "Actor.h"
#include <memory>
#include <string>


namespace antares {
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;
		void Update(float dt);
		void Draw(Renderer& renderer);

		bool Initialize();

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll(bool force = false);

		bool Load(const std::string& filename);
		void Read(const json_t& value);

		template<typename T>
		T* GetActor();

		template<typename T = Actor>
		T* GetActor(const std::string& name);

		friend class Actor;

	private:
		std::list<std::unique_ptr<Actor>> actors;
	};

	template<typename T>
	inline T* Scene::GetActor() {
		for (auto& actor : actors) {
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}
	template<typename T>
	inline T* Scene::GetActor(const std::string& name) {
		for (auto& actor : actors) {
			if (actor->name == name) {
				T* result = dynamic_cast<T*>(actor.get());
				if (result) return result;
			}
		}
		return nullptr;
	}
}