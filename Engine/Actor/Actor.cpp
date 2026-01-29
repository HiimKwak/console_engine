#include <iostream>
#include <Windows.h> // 윈도우의 콘솔 API. 다른 운영체제 API는 헤더가 다르다

#include "Actor.h"

namespace Wanted
{
	Actor::Actor(const char image, const Vector2& position)
		: image(image), position(position)
	{
	}
	Actor::~Actor()
	{
	}

	void Actor::BeginPlay()
	{
		// toggle after receiving begin play call
		hasPlayBegun = true;
	}
	void Actor::Tick(float deltaTime)
	{
	}
	void Actor::Draw()
	{
		// 액터의 현재 좌표로 콘솔 좌표 위치 이동
		COORD coord = {};
		coord.X = static_cast<short>(position.x);
		coord.Y = static_cast<short>(position.y);
		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			coord
		);

		// 이동한 좌표에서 글자 그리기
		std::cout << image;
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		// 액터의 좌표로 콘솔 좌표 위치 이동
		// 액터의 현재 좌표로 콘솔 좌표 위치 이동
		COORD coord = {};
		coord.X = static_cast<short>(position.x);
		coord.Y = static_cast<short>(position.y);
		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			coord
		);

		// 해당 위치의 글자 값 지우기 (빈칸 그리기)
		std::cout << ' ';

		// 새로운 위치 설정
		position = newPosition;
	}

}