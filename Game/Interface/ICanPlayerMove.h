#pragma once

#include "Math/Vector2.h"

// 플레이어가 이동할 위치를 판단해주는 인터페이스.
// 인터페이스(C++) = 순수 가상함수를 가지는 클래스
class ICanPlayerMove
{
public:
	virtual bool CanMove(
		const Wanted::Vector2& playerPosition, // 현재 플레이어 위치
		const Wanted::Vector2& nextPosition // 이동하려는 위치
	) = 0;
};