#include "Engine.h"
#include <iostream>
#include <Windows.h>

namespace Wanted
{
	Engine::Engine()
	{
	}
	Engine::~Engine()
	{
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
				ProcessInput();

				// processing one frame
				Tick(deltaTime);
				Draw();

				// update previous time
				previousTime = currentTime;

				// update key states
				// read each key input
				// must use OS specific API
				for (int ix = 0; ix < 255; ++ix)
				{
					keyStates[ix].wasKeyDown = keyStates[ix].isKeyDown;

				}
			}

		}
		// todo: cleanup
		std::cout << "Engine has been shutdown..." << std::endl;
	}
	void Engine::Quit()
	{
		isQuit = true;
	}
	bool Engine::GetKeyDown(int keyCode)
	{
		return keyStates[keyCode].isKeyDown && !keyStates[keyCode].wasKeyDown;
	}
	bool Engine::GetKeyUp(int keyCode)
	{
		return keyStates[keyCode].wasKeyDown && !keyStates[keyCode].isKeyDown;
	}
	bool Engine::GetKey(int keyCode)
	{
		return keyStates[keyCode].isKeyDown;
	}
	void Engine::ProcessInput()
	{
		// read each key input
		// must use OS specific API
		for (int ix = 0; ix < 255; ++ix)
		{
			keyStates[ix].isKeyDown = (GetAsyncKeyState(ix) & 0x8000) > 0 ? true : false;

		}
	}
	void Engine::Tick(float deltaTime)
	{
		std::cout
			<< "DeltaTime: " << deltaTime 
			<< ", FPS: " << (1.0f / deltaTime) << std::endl;

		// quit when ESC is pressed
		if (GetKeyDown(VK_ESCAPE))
		{
			Quit();
		}
	}
	void Engine::Draw()
	{
	}
}
