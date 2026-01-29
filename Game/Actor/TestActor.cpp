#include <iostream>
#include <Windows.h>

#include "TestActor.h"
#include "Core/Input.h"
#include "Engine/Engine.h"

using namespace Wanted;

TestActor::TestActor()
	: super('T', Vector2(2, 3)) // Actor()가 정답이나 RTTI Macro로 사용가능
{
}

void TestActor::BeginPlay()
{
	// C++는 부모함수 가리키는 포인터가 없음
	Actor::BeginPlay();

	//std::cout << "TestActor::BeginPlay().\n";
}

void TestActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	if (Input::Get().GetKeyDown('Q'))
	{
		// todo: 게임 엔진 종료 요청
		Engine::Get().Quit();
	}

	// 이동
	if (Input::Get().GetKey(VK_RIGHT) && GetPosition().x < 50)
	{
		Vector2 newPosition = GetPosition();
		newPosition.x += 1;
		SetPosition(newPosition);
	}

	if (Input::Get().GetKey(VK_LEFT) && GetPosition().x > 0)
	{
		Vector2 newPosition = GetPosition();
		newPosition.x -= 1;
		SetPosition(newPosition);
	}
	if (Input::Get().GetKey(VK_DOWN) && GetPosition().y < 10)
	{
		Vector2 newPosition = GetPosition();
		newPosition.y += 1;
		SetPosition(newPosition);
	}

	if (Input::Get().GetKey(VK_UP) && GetPosition().y > 0)
	{
		Vector2 newPosition = GetPosition();
		newPosition.y -= 1;
		SetPosition(newPosition);
	}

	/*std::cout
		<< "TestActor::Tick(). deltaTime: " << deltaTime
		<< ", FPS: " << (1.f / deltaTime)
		<< std::endl;*/
}

void TestActor::Draw()
{
	Actor::Draw();
}
