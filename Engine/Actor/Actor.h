#pragma once

namespace Wanted
{
	class Actor
	{
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
