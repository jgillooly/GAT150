#include "Scene.h"
#include "Renderer/Renderer.h"
#include "Components/CircleCollisionComponent.h"
#include "Core/Json.h"

namespace antares {
	void Scene::Update(float dt) {
		//update & remove destroyed actors
		auto iter = actors.begin();
		while (iter != actors.end()) {
			if ((*iter)->active) (*iter)->Update(dt);
			(((*iter)->m_destroyed) ? iter = actors.erase(iter) : iter++);
			//if ((*iter)->m_destroyed) {
			//	iter = m_actors.erase(iter);
			//}
			//else {
			//	iter++;
			//}
			
		}
		//check collisions
		//for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) {
		//	for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++) {
		//		CollisionComponent* collision1 = (*iter1)->GetComponent<CollisionComponent>();
		//		CollisionComponent* collision2 = (*iter2)->GetComponent<CollisionComponent>();

		//		if (!collision1 || !collision2) continue;

		//		if (collision1->CheckCollision(collision2)) {
		//			if (!(*iter1)->m_destroyed && !(*iter2)->m_destroyed) {
		//				(*iter1)->OnCollision(iter2->get());
		//				(*iter2)->OnCollision(iter1->get());
		//				//std::cout << "Collision!" << (*iter1)->m_tag << " " << (*iter2)->m_tag << std::endl; // uncomment for debug :)
		//			}
		//		}
		//	}
		//}
	}

	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : actors) {
			if (actor->active) actor->Draw(renderer);
		}
	}

	bool Scene::Initialize() {
		for (auto& actor : actors) {
			actor->Initialize();
		}

		return true;
	}

	void Scene::Add(std::unique_ptr<Actor> actor) {
		actor->m_scene = this;
		actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll(bool force) {
		auto iter = actors.begin();
		while (iter != actors.end()) {
			if (!(*iter)->persistent || force) {
				iter = actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}
	bool Scene::Load(const std::string& filename) {
		rapidjson::Document document;
		if (!Json::Load(filename, document)) {
			//ERROR_LOG("Could not load scene file" << filename;);
			return false;
		}
		Read(document);
		return true;
	}
	void Scene::Read(const json_t& value) {
		bool isit = GET_DATA(value, actors).IsArray();
		if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray()) {
			auto actorArray = GET_DATA(value, actors).GetArray();
			for (auto& actorValue : actorArray) {
				std::string type;
				READ_DATA(actorValue, type);
				auto actor = CREATE_CLASS_BASE(Actor, type);
				actor->Read(actorValue);
				if (actor->prototype) {
					std::string name = actor->name;
					Factory::Instance().RegisterPrototype(name, std::move(actor));
				}
				else {
					Add(std::move(actor));
				}

				
			}
		}
	}
}