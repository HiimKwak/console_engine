#pragma once
#pragma warning(disable: 4251)

// STL(Standard Template Library)
#include <vector> // 동적 배열
#include "Common/Common.h"

namespace Wanted
{
	class Actor;

	// 목표: 레벨에 있는 모든 액터 관리
	class WANTED_API Level
	{
	public:
		Level();
		virtual ~Level();

		// game play events
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// add actor to level
		void AddNewActor(Actor* newActor);

	protected:
		std::vector<Actor*> actors;
	};
}

