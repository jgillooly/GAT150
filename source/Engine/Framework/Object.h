#pragma once
#include <string>

namespace antares {
	class Object {
	public:
		Object() = default;
		Object(const std::string& name) : m_identifier{ name } {}
		virtual ~Object() { OnDestroy(); }


		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	protected:
		std::string m_identifier;
	};
}