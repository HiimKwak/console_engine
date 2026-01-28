#pragma once

#include "Common/RTTI.h"

namespace Wanted
{
	class WANTED_API Actor : public RTTI // dll 바깥에서 접근가능하게 열어주는 키워드
	{
		// RTTI 코드 추가
		RTTI_DECLARATIONS(Actor, RTTI)

	public:
		Actor();
		virtual ~Actor();

		// game play events
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		//getter
		inline bool HasPlayBegun() const { return hasPlayBegun; }
		bool IsActive() const
		{
			return isActive && !destroyRequested;
		}

	protected:
		// check wheter begin play has been called
		bool hasPlayBegun = false;

		// active state
		bool isActive = true;

		// whether received destroy request on current frame
		bool destroyRequested = false;
	};
}
