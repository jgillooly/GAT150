#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Event/EventManager.h"

class SpaceGame : public antares::Game, antares::IEventListener {
public:
	enum eState {
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};
public:
	// Inherited via Game
	virtual bool Initialize() override;

	virtual void Shutdown() override;

	virtual void Uptdate(float dt) override;

	virtual void Draw(antares::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }
	void AddPoints(const antares::Event& event);
	void OnPlayerDeath(const antares::Event& event);

private:
	eState m_state;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;
	float m_deathTimer = 0;
	std::shared_ptr<antares::Font> m_font;
	std::shared_ptr<antares::Text> m_scoreText;
	std::shared_ptr<antares::Text> m_titleText;
	std::shared_ptr<antares::Text> m_livesText;
	std::shared_ptr<antares::Text> m_gameOverText;
	std::shared_ptr<antares::Text> m_boostText;
	std::shared_ptr<antares::Text> m_HSText;
	antares::ParticleSystem m_PS;
	int m_milestone = 0;
	int highscore = 0;

};