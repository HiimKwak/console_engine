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

	protected:

	};
}
