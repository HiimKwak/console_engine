#include <iostream>
#include <Windows.h>

#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Box.h"
#include "Level/Level.h"
#include "Game/Game.h"

#include "Interface/ICanPlayerMove.h"

using namespace Wanted;

Player::Player(const Vector2& position)
	: super('P', position, Color::Red) // Actor()가 정답이나 RTTI Macro로 사용가능
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
	super::Tick(deltaTime);

	// 게임 중 ESC키 입력 처리
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
		return;
	}

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

	// 인터페이스 확인
	static ICanPlayerMove* canPlayerMoveInterface = nullptr;
	if (!canPlayerMoveInterface && GetOwner()) // null check
	{
		// 인터페이스로 형변환
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());
	}

	// 이동
	if (Input::Get().GetKeyDown(VK_RIGHT) && GetPosition().x < 50)
	{
		// 이동 가능 여부 판단
		Vector2 newPosition(GetPosition().x + 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}
	if (Input::Get().GetKeyDown(VK_LEFT) && GetPosition().x > 0)
	{
		// 이동 가능 여부 판단
		Vector2 newPosition(GetPosition().x - 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}
	if (Input::Get().GetKeyDown(VK_DOWN) && GetPosition().y < 15)
	{
		// 이동 가능 여부 판단
		Vector2 newPosition(GetPosition().x, GetPosition().y + 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}
	if (Input::Get().GetKeyDown(VK_UP) && GetPosition().y > 0)
	{
		// 이동 가능 여부 판단
		Vector2 newPosition(GetPosition().x, GetPosition().y - 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}
}

void Player::Draw()
{
	Actor::Draw();
}
