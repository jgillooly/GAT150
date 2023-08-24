#include <iostream>
#include "Core/Core.h"
#include <chrono>
#include "Renderer/Renderer.h"
#include "../../Input/InputSystem.h"
#include <thread>
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include <cassert>
#include <array>
#include <map>
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

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

template <typename T>
void print(const std::string& s, const T& container) {
	std::cout << s << std::endl;
		for (auto element : container) {
			std::cout << element << " ";
		}
	std::cout << std::endl;
}

void print_arg(int count, ...) {
	va_list args;



	va_start(args, count);
	for (int i = 0; i < count; ++i) {
		std::cout << va_arg(args, const char*) << std::endl;
	}
	va_end(args);
}

void zero(int v) {
	v = 0;
}

void zero(int* v) {
	*v = 0;
}

void zero_ref(int& v) {
	v = 0;
}

void print(int i) {
	cout << i << endl;
}

int add(int i1, int i2) { return i1 + i2; }
int sub(int i1, int i2) { return i1 - i2; }

class A {
public:
	int add(int i1, int i2) { return i1 + i2; }
	int sub(int i1, int i2) { return i1 - i2; }
};

union Data {
	int i;
	bool b;
	char str[6];
};

int main(int argc, char* argv[]) {

	Data data;


	void (*func_ptr)(int)= &print;
	func_ptr(5);

	int(*op_ptr)(int, int);
	op_ptr = &add;

	std::function<int(int, int)> op;

	op = add;
	A a;

	op = std::bind(&A::add, &a, std::placeholders::_1, std::placeholders::_2);


	
	{ if (antares::Logger::Instance().Log(antares::LogLevel::Info, "C:\\Users\\Joshua\\source\\repos\\GAT150\\source\\Game\\Game\\main.cpp", 67)) {
		antares::Logger::Instance() << "Initialize Game" << "\n";
	} };

	antares::MemoryTracker::Initialize();
	antares::Factory::Instance();
	antares::PhysicsSystem::Instance().Initialize();
	antares::seedRandom((unsigned int)time(NULL));
	antares::setFilePath("Assets");
	size_t size;
	antares::getFileSize("scene.json", size);

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


	
	


	


	shared_ptr<antares::Texture> texture = GET_RESOURCE(antares::Texture, "planet.jpg", antares::g_renderer);
	//texture->Load("planet.jpg", antares::g_renderer);



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
		antares::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);
		//text->Draw(antares::g_renderer, 400, 300);
		renderer.SetColor(255, 255, 255, SDL_ALPHA_OPAQUE);
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