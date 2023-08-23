#pragma once
#include "Event.h"
#include "Framework/Singleton.h"
#include <map>
#include <list>
#include <functional>

#define EVENT_SUBSCRIBE(id, function)	antares::EventManager::Instance().Subscribe(id, this, std::bind(&function, this, std::placeholders::_1));
#define EVENT_UNSUBSCRIBE(id)			antares::EventManager::Instance().Unsubscribe(id, this);

namespace antares {
	class IEventListener {
		//
	};
	class EventManager : public Singleton<EventManager> {
	public:
		using eventFunction = std::function<void(const Event&)>;

		struct EventDispatcher {
			eventFunction function; //function called on event
			IEventListener* listener = nullptr; //object that can listen for events
		};
		friend class Singleton;
	public:
		EventManager() = default;

		void Update(float dt);

		void Subscribe(Event::id_t id, IEventListener* listener, eventFunction function);
		void Unsubscribe(Event::id_t id, IEventListener* listener);

		void DispatchEvent(Event::id_t id, Event::data_t data, void* sender = nullptr, float time = 0);
	private:
		std::map < Event::id_t, std::list<EventDispatcher>> m_dispatchers;
	};
}