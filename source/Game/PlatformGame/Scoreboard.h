#pragma once
#include "Framework/Actor.h"
#include "Framework/Componenets/TextRenderComponent.h"
#include "Framework/Event/EventManager.h"

#include <string>
namespace antares {
	class Scoreboard : public antares::Actor, antares::IEventListener {
	public:
		Scoreboard() = default;
		CLASS_DECLARATION(Scoreboard)

		bool Initialize() override;

		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;
		void UpdateScore(const antares::Event& event);
	private:
		TextRenderComponent* m_text = nullptr;
	};
}