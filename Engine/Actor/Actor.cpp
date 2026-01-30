#include <iostream>
#include <Windows.h> // 윈도우의 콘솔 API. 다른 운영체제 API는 헤더가 다르다

#include "Util/Util.h"
#include "Actor.h"
#include "Core/Renderer.h"

namespace Wanted
{
	Actor::Actor(const char image, const Vector2& position, Color color)
		: image(image), position(position), color(color)
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
		Renderer::Draw(position, color, image);
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		Renderer::Draw(position, ' ');

		// 새로운 위치 설정
		position = newPosition;
	}

}