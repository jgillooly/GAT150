#pragma once
#include <memory>
#include <map>
#include <string>
#include "Object.h"
#include "Singleton.h"
#include "Core/Logger.h"

#define CREATE_CLASS(classname) antares::Factory::Instance().Create<antares::classname>(#classname);

namespace antares {
	class CreatorBase {
	public:
		virtual ~CreatorBase() = default;
		virtual std::unique_ptr<class Object> Create() = 0;
	};

	template <typename T>
	class Creator : public CreatorBase {
	public:
		std::unique_ptr<class Object> Create() {
			return std::make_unique<class Object>();
		}
	};

	class Factory : public Singleton<Factory> {
	public:
		template <typename T>
		void Register(const std::string& key);

		template <typename T>
		std::unique_ptr<T> Create(const std::string& key);

		friend class Singleton;
	private:
		std::map<std::string, std::unique_ptr<antares::CreatorBase>> m_registry;
	protected:
		Factory() = default;
	};


	template<typename T>
	inline void Factory::Register(const std::string& key) {
		m_registry[key] = std::make_unique<Creator<T>>();
		INFO_LOG("Registered in Factory")
	}

	template<typename T>
	inline std::unique_ptr<T> Factory::Create(const std::string& key) {
		auto iter = m_registry.find(key);
		if (iter != m_registry.end()) {
			return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->Create().release()));
		}
	}
}

