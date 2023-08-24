#include "PlatformGame.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Audio/AudioSystem.h"
#include "../../Input/InputSystem.h"
#include <memory>
#include "Framework/Framework.h"

bool PlatformGame::Initialize() {

	//load audio
	antares::g_audioSystem.AddAudio("explosion", "Explosion.wav");
	antares::g_audioSystem.AddAudio("laser", "LaserShoot.wav");
	antares::g_audioSystem.AddAudio("music", "Music.wav");

	m_scene = std::make_unique<antares::Scene>();
	bool success = m_scene->Load("scenes/platformScene.json");
	m_scene->Initialize();
	m_state = PlatformGame::Title;
	antares::g_particleSystem = antares::ParticleSystem(10000);

	antares::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&PlatformGame::AddPoints, this, std::placeholders::_1));
	antares::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&PlatformGame::OnPlayerDeath, this, std::placeholders::_1));

	return true;
}

void PlatformGame::Shutdown() {
}

void PlatformGame::Uptdate(float dt) {
	switch (m_state) {
	case PlatformGame::Title:
	{

		break;
	}
	case PlatformGame::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case PlatformGame::StartLevel:
	{ 
	break; }
	case PlatformGame::Game:
		
		break;
	case PlatformGame::PlayerDead:
		
		break;
	case PlatformGame::GameOver:
		
		break;
	default:
		break;
	}

	m_scene->Update(dt);
	antares::g_particleSystem.Update(dt);
}

void PlatformGame::Draw(antares::Renderer& renderer) {

	m_scene->Draw(renderer);
	antares::g_particleSystem.Draw(renderer);
}

void PlatformGame::AddPoints(const antares::Event& event) {
	m_score += std::get<int>(event.data);

}

void PlatformGame::OnPlayerDeath(const antares::Event& event) {
	m_lives--;
	SetState(eState::PlayerDead);
}