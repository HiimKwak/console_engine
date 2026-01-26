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
		// shoule be able to call BeginPlay only once per actor
		// because actors can be generated dynamically during gameplay
		for (Actor* actor : actors)
		{
			if (actor->HasPlayBegun())
			{
				continue;
			}

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
	void Level::AddNewActor(Actor* newActor)
	{
		// todo: 프레임 처리 고려해서 추가 작업 필요
		actors.emplace_back(newActor);
	}
}