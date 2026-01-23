#pragma once

namespace  Wanted
{
	class Engine
	{
		struct KeyState // 구조체는 데이터에, 클래스는 기동에 초점
		{
			// key pressed or not on this frame
			bool isKeyDown = false;
			// key pressed or not on previous frame
			bool wasKeyDown = false;
		};

	public:
		Engine();
		~Engine();

		// game loop
		void Run();
		void Quit();

		// input checker
		bool GetKeyDown(int keyCode); // called when key pressed newly
		bool GetKeyUp(int keyCode); // called when pressed key cancelled 
		bool GetKey(int keyCode); // called when key is being pressed
		
	private:
		// process input
		void ProcessInput();

		// update
		void Tick(float deltaTime);

		// draw/render
		void Draw();

	private:
		// quit flag
		bool isQuit = false;
		// key states
		KeyState keyStates[255] = { };
	};
}



