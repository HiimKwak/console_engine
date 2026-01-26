#pragma once

// STL(Standard Template Library)
# include <vector> // 동적 배열

namespace Wanted
{
	class Actor;

	// 목표: 레벨에 있는 모든 액터 관리
	class Level
	{
	public:
		Level();
		virtual ~Level();

		// game play events
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

	protected:
		std::vector<Actor*> actors;

	};
}

