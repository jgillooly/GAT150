#pragma once
namespace antares {
	class Component {
	public:
		virtual void Update(float dt) = 0;
		friend class Actor;
	protected:
		Actor* m_owner = nullptr;
	};
}