#include <iostream>
#include <Windows.h>

#include "Engine.h"
#include "Level/Level.h"
#include "Core/Input.h"

namespace Wanted
{
	Engine* Engine::instance = nullptr;
	Engine::Engine()
	{
		instance = this;

		// input manager 생성
		input = new Input();
	}
	Engine::~Engine()
	{
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}
		if (input)
		{
			delete input;
			input = nullptr;
		}
	}
	void Engine::Run()
	{
		// Accuracy of Timer
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		//int64_t = STL 타입 재정의된 타입, __int64와 동일함
		__int64 currentTime = 0;
		__int64 previousTime = 0;

		// Hardware Timer //참고: timeGetTime(); milliseconds, 게임 외 소프트웨어에서 쓰이는 타이머 
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);

		// initialize previous time with currTime once at the start of the loop
		currentTime = time.QuadPart;
		previousTime = currentTime;

		// target frame rate
		float targetFrameRate = 120.0f;
		float oneFrameTime = 1.0f / targetFrameRate;

		while (!isQuit)
		{
			// current time
			QueryPerformanceCounter(&time);
			currentTime = time.QuadPart;

			// calculate delta time
			float deltaTime = static_cast<float>(currentTime - previousTime);

			// transform to seconds
			deltaTime /= static_cast<float>(frequency.QuadPart);

			// frame limiting
			if (deltaTime >= oneFrameTime)
			{
				input->ProcessInput();

				// processing one frame
				BeginPlay();
				Tick(deltaTime);
				Draw();


				// update previous time
				previousTime = currentTime;

				input->SavePreviousInputStates();
			}

		}
		// todo: cleanup
		std::cout << "Engine has been shutdown..." << std::endl;
	}
	void Engine::Quit()
	{
		isQuit = true;
	}
	void Engine::SetNewLevel(Level* newLevel)
	{
		// todo: temporary, must not delete level when switching levels in actual game
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}

		// level setting
		mainLevel = newLevel;
	}

	Engine& Engine::Get()
	{
		if (!instance)
		{
			std::cout << "Error: Engine::Get(). instance is null\n";
			__debugbreak();
		}
		return *instance;
	}

	void Engine::BeginPlay()
	{
		if (!mainLevel)
		{
			std::cout << "No level is set as main level!" << std::endl;
			return;
		}
		mainLevel->BeginPlay();
	}
	void Engine::Tick(float deltaTime)
	{
		//std::cout
		//	<< "DeltaTime: " << deltaTime 
		//	<< ", FPS: " << (1.0f / deltaTime) << std::endl;

		if (!mainLevel)
		{
			std::cout << "No level is set as main level!" << std::endl;
			return;
		}

		// 
		mainLevel->Tick(deltaTime);
	}
	void Engine::Draw()
	{
		if (!mainLevel)
		{
			std::cout << "No level is set as main level!" << std::endl;
			return;
		}

		// 
		mainLevel->Draw();
	}
}
