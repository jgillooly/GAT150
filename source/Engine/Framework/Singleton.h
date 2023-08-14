#pragma once
namespace antares {
	template<typename T>
	class Singleton {
	public:
		Singleton(const Singleton& other) = delete;
		Singleton& operator = (const Singleton&) = delete;
		static T& Instance() {
			static T instance;
			return instance;
		}
	protected:
		Singleton() = default;
	};
}