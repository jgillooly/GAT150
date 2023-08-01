#include <iostream>
#include "Core/Core.h"
#include <chrono>
#include "Renderer/Renderer.h"
#include "../../Input/InputSystem.h"
#include <thread>
#include "Audio/AudioSystem.h"
#include "Framework/Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Framework/Scene.h"
#include "Weapon.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "SpaceGame.h"

using namespace std;

class Star {
public:
	Star(const antares::Vector2& position, const antares::Vector2& velocity) : m_position{ position }, m_velocity{ velocity } {};
	void Update() {
		m_position += m_velocity * antares::g_time.getDeltaTime();
	}
public:
	antares::Vector2 m_position;
	antares::Vector2 m_velocity;
};

int main(int argc, char* argv[]) {
	INFO_LOG

	std::cout << "Start Game" << std::endl;


	antares::MemoryTracker::Initialize();
	{
		//std::unique_ptr<int> up = std::make_unique<int>(10);
	}
	std::string stri = "test";

	antares::seedRandom((unsigned int)time(NULL));
	antares::setFilePath("assets");
	antares::writeFile("Test.txt", stri);
	vector<Star> stars;
	antares::Renderer renderer;
	antares::g_renderer.CreateWindow("window", 800, 600);
	antares::g_renderer.Initialize();
	cout << "Window created: " << antares::g_renderer.GetWidth() << "x" << antares::g_renderer.GetHeight() << std::endl;

	antares::g_inputSystem.Initialize();

	antares::g_audioSystem.Initialize();


	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();




	std::vector<antares::vec2> points{ {-10, 5}, { 10, 5 }, { 0, -5 }, { -10, 5 } };

	antares::vec2 v{5, 5};
	v.Normalize();

	for (int i = 0; i < 1000; i++) {
		stars.push_back(Star(antares::Vector2(antares::random(antares::g_renderer.GetWidth()), antares::random(antares::g_renderer.GetHeight())),
			antares::Vector2(100,100)));
	}


	
	


	
	for (int i = 0; i < 5; i++) {
		float rotat = antares::randomf(antares::TwoPi);
		antares::Transform t1{ {400, 300}, rotat, 2};
		unique_ptr<Enemy> enemy = std::make_unique<Enemy>((float)antares::random(150, 250), (float)200, t1, antares::g_manager.Get("Diamond.txt"));
		enemy->m_tag = "Enemy";
		//scene.Add(std::move(enemy));
	}

	bool quit = false;

	//game loop
	while (!quit) {
		//update systems
		antares::g_audioSystem.Update();
		antares::g_time.Tick();
		antares::g_inputSystem.Update();
		game->Uptdate(antares::g_time.getDeltaTime());
		//get inputs
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}
		if(antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !antares::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			antares::g_audioSystem.PlayOneShot("laser");
		}

		if (antares::g_inputSystem.GetMouseButtonDown(0)) {
			cout << "Mouse Pressed" << endl;
			cout << "Mouse Position: (" << antares::g_inputSystem.GetMousePosition().x << "," << antares::g_inputSystem.GetMousePosition().y << ")" << endl;
		}

		//drawing
		antares::g_renderer.SetColor(0, 0, 0, 0);
		antares::g_renderer.BeginFrame();
		//text->Draw(antares::g_renderer, 400, 300);
		//renderer.SetColor(255, 255, 255, SDL_ALPHA_OPAQUE);
		for (auto& point : stars) {
			int r = antares::random(256);
			int g = antares::random(256);
			int b = antares::random(256);
			antares::g_renderer.SetColor(255, 255, 255, SDL_ALPHA_OPAQUE);
			point.Update();
			if (point.m_position.x > antares::g_renderer.GetWidth()) point.m_position.x = 0;
			if (point.m_position.y > antares::g_renderer.GetHeight()) point.m_position.y = 0;

			antares::g_renderer.DrawPoint(point.m_position.x, point.m_position.y);
		}
		//scene.Update(antares::g_time.getDeltaTime());
		//scene.Draw(antares::g_renderer);
		//enemy.Update(antares::g_time.getDeltaTime());
		//enemy.Draw(antares::g_renderer);
		//model.Draw(renderer, transform.position, transform.rotation, transform.scale);
		game->Draw(antares::g_renderer);

		antares::g_renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(15));
	}

	
	//scene.RemoveAll();

	antares::MemoryTracker::DisplayInfo();
	return 0;
}