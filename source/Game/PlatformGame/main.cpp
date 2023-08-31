#include <iostream>
#include "Core/Core.h"
#include <chrono>
#include "Renderer/Renderer.h"
#include "../../Input/InputSystem.h"
#include <thread>
#include "Audio/AudioSystem.h"
#include <cassert>
#include <array>
#include <map>
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"
#include <functional>
#include "PlatformGame.h"

using namespace std;



int main(int argc, char* argv[]) {


	antares::MemoryTracker::Initialize();
	antares::Factory::Instance();
	antares::PhysicsSystem::Instance().Initialize();
	antares::seedRandom((unsigned int)time(NULL));
	antares::setFilePath("Assets");

	antares::Renderer renderer;
	antares::g_renderer.CreateWindow("window", 800, 600);
	antares::g_renderer.Initialize();
	cout << "Window created: " << antares::g_renderer.GetWidth() << "x" << antares::g_renderer.GetHeight() << std::endl;

	antares::g_inputSystem.Initialize();

	antares::g_audioSystem.Initialize();
	antares::g_audioSystem.AddAudio("jump", "audio/LaserShoot.wav");
	antares::g_audioSystem.PlayOneShot("jump");

	unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
	game->Initialize();

	bool quit = false;

	//game loop
	while (!quit) {
		//update systems
		antares::g_audioSystem.Update();
		antares::g_time.Tick();
		antares::g_inputSystem.Update();
		antares::PhysicsSystem::Instance().Update(antares::g_time.getDeltaTime());
		game->Uptdate(antares::g_time.getDeltaTime());
		//get inputs
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !antares::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
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
		renderer.SetColor(255, 255, 255, SDL_ALPHA_OPAQUE);

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