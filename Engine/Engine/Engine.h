#pragma once

#include "Common/Common.h"

namespace  Wanted
{
	class Input;

	class WANTED_API Engine
	{
	public:
		Engine();
		~Engine();

		// game loop
		void Run();
		void Quit();

		// add new level
		void SetNewLevel(class Level* newLevel);

		static Engine& Get();

	private:
		// begin game play
		void BeginPlay();

		// update
		void Tick(float deltaTime);

		// draw/render
		void Draw();

	private:
		// quit flag
		bool isQuit = false;
		// input manager
		Input* input = nullptr;
		// main level
		class Level* mainLevel = nullptr;

		static Engine* instance;
	};
}
