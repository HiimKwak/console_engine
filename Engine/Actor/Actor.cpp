#include "Actor.h"

namespace Wanted
{
	Actor::Actor()
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
	}

}