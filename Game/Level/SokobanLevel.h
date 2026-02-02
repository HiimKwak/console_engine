#pragma once
#include "Level/Level.h"
#include "Common/Common.h"
#include "Interface/ICanPlayerMove.h"

class SokobanLevel : public Wanted::Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();

private:
	// 게임에서 사용할 맵을 로드하는 함수.
	void LoadMap(const char* filename);

	// ICanPlayerMove을(를) 통해 상속됨
	virtual bool CanMove(const Wanted::Vector2& playerPosition, const Wanted::Vector2& nextPosition) override;
};

