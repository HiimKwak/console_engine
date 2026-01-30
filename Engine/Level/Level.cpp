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
		// 프레임 처리 고려해서 추가 작업 필요
		//actors.emplace_back(newActor);
		addRequestedActors.emplace_back(newActor);
	}

	void Level::ProcessAddAndDestoryActors()
	{
		for (int ix = 0; ix < static_cast<int>(actors.size());)
		{
			// 제거 요청된 액터가 있는지 확인
			if (actors[ix]->DestroyRequested())
			{
				// 삭제 처리
				delete actors[ix]; // 힙 메모리 해제
				actors.erase(actors.begin() + ix); // 배열에서도 삭제 후 앞당기기

				continue;
			}

			++ix;
		}

		if (addRequestedActors.size() == 0)
		{
			return;
		}

		for (Actor* const actor : addRequestedActors)
		{
			actors.emplace_back(actor); // 추가요청받은 actor 주소만 actors 배열에 추가
		}

		addRequestedActors.clear();
	}
}