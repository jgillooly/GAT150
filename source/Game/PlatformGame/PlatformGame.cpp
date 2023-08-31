#include "PlatformGame.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Audio/AudioSystem.h"
#include "../../Input/InputSystem.h"
#include <memory>
#include "Framework/Framework.h"
#include "Enemy.h"
#include "Framework/Actor.h"
#include "Framework/Componenets/TextRenderComponent.h"
#include "Player.h"

bool PlatformGame::Initialize() {

	//load audio
	antares::g_audioSystem.AddAudio("explosion", "Explosion.wav");
	antares::g_audioSystem.AddAudio("laser", "LaserShoot.wav");
	antares::g_audioSystem.AddAudio("music", "Music.wav");

	m_scene = std::make_unique<antares::Scene>();
	bool success = m_scene->Load("scenes/platformScene.json");
	m_scene->Load("scenes/tilemap.json");
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
		//auto actor = INSTANTIATE(Actor,"Crate");
		//actor->transform.position = { antares::random(0,antares::g_renderer.GetWidth()), 100 };
		//actor->Initialize();
		//m_scene->Add(std::move(actor));
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !antares::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			auto title = m_scene->GetActor<antares::Actor>("Title");
			auto text = title->GetComponent<antares::TextRenderComponent>();
			text->SetText("");
			m_state = eState::StartGame;
		}

		break;
	}
	case PlatformGame::StartGame:
	{
		if (!m_scene->GetActor<antares::Actor>("Coin")) {
			auto coin = INSTANTIATE(Actor, "Coin");
			coin->Initialize();
			m_scene->Add(std::move(coin));
		}
		auto player = INSTANTIATE(Player, "Player");
		player->Initialize();
		m_scene->Add(std::move(player));
		m_state = eState::StartLevel;
		break;
	}
	case PlatformGame::StartLevel:
	{
		m_state = eState::Game;
	break; }
	case PlatformGame::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->transform = antares::Transform{ { antares::random(800), antares::random(600) }, antares::randomf(antares::TwoPi), 1 };
			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}
		
		break;
	case PlatformGame::PlayerDead:
	{
		auto title = m_scene->GetActor<antares::Actor>("Title");
		auto text = title->GetComponent<antares::TextRenderComponent>();
		text->SetText("Game Over");
		m_state = eState::GameOver;
		break;
	}
	case PlatformGame::GameOver:
	{
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !antares::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			auto title = m_scene->GetActor<antares::Actor>("Title");
			auto text = title->GetComponent<antares::TextRenderComponent>();
			text->SetText("Lil Dude");
			//m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	}
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
	std::cout << m_score;
}

void PlatformGame::OnPlayerDeath(const antares::Event& event) {
	m_lives--;
	SetState(eState::PlayerDead);
}