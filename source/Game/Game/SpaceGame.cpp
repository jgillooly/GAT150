#include "SpaceGame.h"
#include "Renderer/Renderer.h"
#include "Player.h"
#include "Enemy.h"
#include "Core/Core.h"
#include "Audio/AudioSystem.h"
#include "../../Input/InputSystem.h"
#include <memory>
#include "Core/Transform.h"
#include "Renderer/ModelManager.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"
#include "Pickup.h"
#include "Core/Core.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/SpriteComponent.h"

bool SpaceGame::Initialize() {	
	// create font / text objects
	m_font = antares::g_resMan.Get<antares::Font>("Quattrocento.ttf", 36);
	m_scoreText = std::make_unique<antares::Text>(m_font);
	m_scoreText->Create(antares::g_renderer, "SCORE: 0000", antares::Color{ 1, 1, 1, 1 });
	
	m_titleText = std::make_unique<antares::Text>(m_font);
	m_titleText->Create(antares::g_renderer, "Asteroids", antares::Color{ 1, 1, 1, 1 });

	m_livesText = std::make_unique<antares::Text>(m_font);
	m_livesText->Create(antares::g_renderer, "Lives:", antares::Color{ 1, 1, 1, 1 });

	m_gameOverText = std::make_unique<antares::Text>(m_font);
	m_gameOverText->Create(antares::g_renderer, "GAME OVER", antares::Color{ 1, 1, 1, 1 });

	m_boostText = std::make_unique<antares::Text>(m_font);
	m_boostText->Create(antares::g_renderer, "Boost: Ready", antares::Color{ 1, 1, 1, 1 });

	m_HSText = std::make_unique<antares::Text>(m_font);
	

	antares::g_audioSystem.AddAudio("explosion", "Explosion.wav");
	antares::g_audioSystem.AddAudio("laser", "LaserShoot.wav");
	antares::g_audioSystem.AddAudio("music", "Music.wav");

	m_scene = std::make_unique<antares::Scene>();
	m_state = SpaceGame::Title;
	antares::g_particleSystem = antares::ParticleSystem(10000);

	std::string HSString = "";
	antares::readFile("Highscore.txt", HSString);
	m_HSText->Create(antares::g_renderer, "High Score: " + HSString, antares::Color{ 1, 1, 1, 1 });
	highscore = std::stoi(HSString);
	antares::g_audioSystem.PlayLoop("music");

	return true;
}

void SpaceGame::Shutdown() {
}

void SpaceGame::Uptdate(float dt) {
	switch (m_state) {
	case SpaceGame::Title:
	{
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}
		
		if (antares::g_inputSystem.GetMouseButtonDown(0)) {
			//antares::EmitterData data;
			//data.burst = true;
			//data.burstCount = 100;
			//data.spawnRate = 200;
			//data.angle = 0;
			//data.angleRange = antares::Pi;
			//data.lifetimeMin = 0.5f;
			//data.lifetimeMax = 1.5f;
			//data.speedMin = 50;
			//data.speedMax = 250;
			//data.damping = 0.5f;
			//data.color = antares::Color{ 1, 0, 0, 1 };
			//antares::Transform transform{ { antares::g_inputSystem.GetMousePosition() }, 0, 1 };
			//auto emitter = std::make_unique<antares::Emitter>(transform, data);
			//emitter->m_lifespan = 1.0f;
			//m_scene->Add(std::move(emitter));
		}

		break;
	}
	case SpaceGame::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case SpaceGame::StartLevel:
		{ antares::Transform transform{ { 400, 300 }, 0, 5 };
		m_milestone = m_score;
		float speed = 100;
		constexpr float turnRate = antares::Degrees2Radians(180.0f);
		std::unique_ptr<Player> player = std::make_unique<Player>(400.0f, antares::Pi, transform, antares::g_manager.Get("Diamond.txt"));
		std::unique_ptr<antares::SpriteComponent> component = std::make_unique<antares::SpriteComponent>();
		component->m_texture = antares::g_resMan.Get<antares::Texture>("planet.jpg");

		player->AddComponent(std::move(component));
		player->m_tag = "Player";
		player->m_game = this;
		m_scene->Add(std::move(player));
		m_state = eState::Game;
		break; }
	case SpaceGame::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			int specialRoll = antares::random(1, 100);
			bool isSpecial = specialRoll <= 50;
			if (isSpecial) std::cout << "Special Spawned" << std::endl;
			float rotat = antares::randomf(antares::TwoPi);
			antares::Transform t1{ {400, 300}, rotat, 2};
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>((float)antares::random(150, 250), (float)200, t1, antares::g_manager.Get("DiamondR.txt"), isSpecial);
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
		}
		if (m_score >= m_milestone + 200) {
 			int x = antares::random(100, antares::g_renderer.GetWidth() - 100);
			int y = antares::random(100, antares::g_renderer.GetHeight() - 100);
			antares::Transform t2{ {x,y}, 0, 10};
   			std::unique_ptr<Pickup> pickup = std::make_unique<Pickup>(t2, antares::g_manager.Get("DiamondH.txt"), 10.0f);
			pickup->m_tag = "Pickup";
			pickup->m_game = this;
			m_scene->Add(std::move(pickup));
			m_milestone = m_score;
			std::cout << "Pickup Spawned at: " << x << "," << y << std::endl;
		}
		break;
	case SpaceGame::PlayerDead:
		if (m_deathTimer >= 3) {
			if (m_lives == 0) {
				m_state = eState::GameOver;
			}
			else {
				m_scene->RemoveAll();
				m_state = eState::StartLevel;
			}
			m_deathTimer = 0;
		}
		else {
			m_deathTimer += dt;
		}
		break;
	case SpaceGame::GameOver:
		if (m_score > highscore) {
			highscore = m_score;
			m_HSText->Create(antares::g_renderer, "New High Score!", antares::Color{ 1, 1, 1, 1 });
			std::string HSString = std::to_string(highscore);
			antares::writeFile("Highscore.txt", HSString);
		}
		break;
	default:
		break;
	}

	//m_scoreText->Create(antares::g_renderer, "Score:" + std::to_string(m_score), antares::Color{ 1, 1, 1, 1 });
	//m_livesText->Create(antares::g_renderer, "Lives:" + std::to_string(m_lives), antares::Color{ 1, 1, 1, 1 });
	Player* p = m_scene->GetActor<Player>();
	std::string status = "";
	if (p) {
		status = p->getBoostStatus();
	}
	//m_boostText->Create(antares::g_renderer, "Boost Status: " + status, antares::Color{ 1, 1, 1, 1 });
	m_scene->Update(dt);
	antares::g_particleSystem.Update(dt);
}

void SpaceGame::Draw(antares::Renderer& renderer) {
	if (m_state == eState::Title) m_titleText->Draw(renderer, (renderer.GetWidth()/2) - 65, renderer.GetHeight()/2);
	if (m_state == eState::GameOver) m_gameOverText->Draw(renderer, 400, 300);
	m_HSText->Draw(renderer, 400, 550);
	if (m_state != eState::Title) {
		m_scoreText->Draw(renderer, 40, 40);
		m_livesText->Draw(renderer, 300, 40);
		m_boostText->Draw(renderer, 40, 500);
	}
	m_scene->Draw(renderer);
	antares::g_particleSystem.Draw(renderer);
}
