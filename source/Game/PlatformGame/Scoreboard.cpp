#include "Scoreboard.h"
namespace antares {
	CLASS_DEFINITION(Scoreboard)
	bool Scoreboard::Initialize() {
		Actor::Initialize();
		m_text = Actor::GetComponent<TextRenderComponent>();
		m_text->SetText("000");
		EVENT_SUBSCRIBE("AddPoints", Scoreboard::UpdateScore);
		return true;
	}

	void Scoreboard::Update(float dt) {

	}

	void Scoreboard::OnCollisionEnter(Actor* other) {
		if (other->tag == "Player" && other->transform.position.y < transform.position.y) {
			m_destroyed = true;
			EventManager::Instance().DispatchEvent("AddPoints", 100);
		}
	}

	void Scoreboard::OnCollisionExit(Actor* other) {

	}

	void Scoreboard::UpdateScore(const antares::Event& event) {
		int score = std::stoi(m_text->text.c_str());
		score += std::get<int>(event.data);
		m_text->SetText(std::to_string(score));
		m_text->Initialize();
	}

	void Scoreboard::Read(const json_t& value) {
		Actor::Read(value);
	}
}