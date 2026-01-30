#include <iostream>
#include <Windows.h>

#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Box.h"
#include "Level/Level.h"

using namespace Wanted;

Player::Player()
	: super('P', Vector2(5, 5), Color::Red) // Actor()가 정답이나 RTTI Macro로 사용가능
{
	sortingOrder = 10;
}

void Player::BeginPlay()
{
	// C++는 부모함수 가리키는 포인터가 없음
	Actor::BeginPlay();

	//std::cout << "Player::BeginPlay().\n";
}

void Player::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	if (Input::Get().GetKeyDown('Q'))
	{
		// todo: 게임 엔진 종료 요청
		Engine::Get().Quit();
	}

	// 스페이스로 박스 생성
	if (Input::Get().GetKeyDown((VK_SPACE)))
	{
		// 박스 생성
		if (owner)
		{
			owner->AddNewActor(new Box(GetPosition())); // 객체를 바로 생성해 넘겨주기보단 타입만 넘겨주고 템플릿으로 내부에서 생성
		}
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
	if (Input::Get().GetKey(VK_DOWN) && GetPosition().y < 15)
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
}

void Player::Draw()
{
	Actor::Draw();
}
