#include "Level.h"
#include "Actor/Actor.h"

namespace Wanted
{
	Level::Level()
	{
	}
	Level::~Level()
	{
		for (Actor*& actor : actors)
		{
			if (actor)
			{
				delete actor;
				actor = nullptr;
			}
		}

		actors.clear(); // vector.clear
	}

	void Level::BeginPlay()
	{
		for (Actor* actor : actors)
		{
			// todo: skip actor if called
			actor->BeginPlay();
		}
	}
	void Level::Tick(float deltaTime)
	{
		for (Actor* actor : actors)
		{
			actor->Tick(deltaTime);
		}
	}
	void Level::Draw()
	{
		for (Actor* actor : actors)
		{
			actor->Draw();
		}
	}
}