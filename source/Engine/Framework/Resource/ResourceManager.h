#pragma once
#include <map>
#include <memory>
#include "Resource.h"
#include "Framework/Singleton.h"

#define GET_RESOURCE(type, filename, ...) antares::ResourceManager::Instance().Get<type>(filename, __VA_ARGS__)

namespace antares {
	class ResourceManager : public Singleton<ResourceManager> {
	public:
		template<typename T, typename ... TArgs>
		res_t<T> Get(const std::string& filename, TArgs ... args);
	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};
	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& filename, TArgs ...args) {
		if (m_resources.find(filename) != m_resources.end()) return std::dynamic_pointer_cast<T>(m_resources[filename]);

		//resource not in resource manager, create it
		res_t<T> resource = std::make_shared<T>();
		//check if creation successful
		resource->Create(filename, args...);
		if (!resource.get()) {
			WARNING_LOG("Could not create resource: " << filename);
			return res_t<T>();
		}
		//add to resman
		m_resources[filename] = resource;
		//return the resource
		return resource;
	}
}