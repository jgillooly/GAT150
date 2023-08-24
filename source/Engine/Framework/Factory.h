#pragma once
#include <memory>
#include <map>
#include <string>
#include "Object.h"
#include "Singleton.h"
#include "Core/Logger.h"
#include <iostream>

#define CREATE_CLASS(classname) antares::Factory::Instance().Create<antares::classname>(#classname);
#define CREATE_CLASS_BASE(classbase, classname) antares::Factory::Instance().Create<antares::classbase>(classname);
#define INSTANTIATE(classbase, classname) antares::Factory::Instance().Create<antares::classbase>(classname);

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
			return std::make_unique<T>();
		}
	};

	template <typename T>
	class PrototypeCreator : public CreatorBase {
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) : prototype { std::move(prototype) } {}
		std::unique_ptr<class Object> Create() {
			return prototype->Clone();
		}
	private:
		std::unique_ptr<T> prototype;
	};

	class Factory : public Singleton<Factory> {
	public:
		template <typename T>
		void Register(const std::string& key);

		template <typename T>
		void RegisterPrototype(const std::string& key, std::unique_ptr<T> prototype);



		template <typename T>
		std::unique_ptr<T> Create(const std::string& key);

		friend class Singleton;
	private:
		std::map<std::string, std::unique_ptr<antares::CreatorBase>> m_registry;
	protected:
		Factory() { std::cout << "AAAAAAA" << std::endl; }
	};


	template<typename T>
	inline void Factory::Register(const std::string& key) {
		m_registry[key] = std::make_unique<Creator<T>>();
		std::cout << key << "Registered in Factory" << std::endl;
	}

	template<typename T>
	inline void Factory::RegisterPrototype(const std::string& key, std::unique_ptr<T> prototype) {
		m_registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
		std::cout << "Prototype Registered in Factory" << std::endl;
	}

	template<typename T>
	inline std::unique_ptr<T> Factory::Create(const std::string& key) {
		auto iter = m_registry.find(key);
		if (iter != m_registry.end()) {
			std::cout << key << "Created" << std::endl;
			return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->Create().release()));
			
		}
		return nullptr;
	}
}

