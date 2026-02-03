#include <iostream>

#include "SokobanLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"
#include "Util/Util.h"

SokobanLevel::SokobanLevel()
{
	//AddNewActor(new Player());
	LoadMap("Stage1.txt");
}

void SokobanLevel::Draw()
{
	super::Draw();

	// 게임 클리어 메세지 출력
	if (isGameClear)
	{
		// 콘솔 위치/색상 설정
		Util::SetConsolePosition(Vector2(30, 0));
		Util::SetConsoleTextColor(Color::White);

		// 게임 클리어 메시지 출력
		std::cout << "Game Clear!";
	}
}

void SokobanLevel::LoadMap(const char* filename)
{
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	if (!file)
	{
		// 표준 오류 콘솔 활용
		std::cerr << "Failed to open map file.\n";
		__debugbreak(); // 디버그 모드 중단
	}

	// 맵 크기 파악: file position 포인터를 파일의 끝으로 이동
	fseek(file, 0, SEEK_END);

	// 이 위치 읽기
	size_t fileSize = ftell(file);

	// file position 처음으로 되돌리기
	rewind(file);

	// 파일에서 데이터 담아올 버퍼 생성
	char* data = new char[fileSize + 1];

	// 데이터 읽기
	size_t readSize = fread(data, sizeof(char), fileSize, file);

	/********************** 맵 그릴 data 채우기 **********************/

	// 읽어온 문자열 분석(parsing)해서 출력
	int index = 0;

	// 객체를 생성할 위치 값
	Wanted::Vector2 position;

	while (true)
	{
		if (index >= fileSize)
		{
			break;
		}

		// 캐릭터 읽기
		char mapCharacter = data[index];
		++index;

		// 개행 문자 처리
		if (mapCharacter == '\n') // text모드로 읽기 때문에 개행문자 정리된 상태로 읽을 수 있음
		{
			++position.y;
			position.x = 0;
			continue;
		}

		/*
		* # = 벽
		* . = 바닥
		* p = 플레이어
		* b = box
		* t = 타겟
		*/
		switch (mapCharacter)
		{
		case '#':
		case '1':
			AddNewActor(new Wall(position));
			break;
		case '.':
			AddNewActor(new Ground(position));
			break;
		case 'p':
			AddNewActor(new Player(position));
			// 플레이어 이동 후 이전 자리에 땅 생성
			AddNewActor(new Ground(position));
			break;
		case 'b':
			AddNewActor(new Box(position));
			// 박스 이동 후 이전 자리에 땅 생성
			AddNewActor(new Ground(position));
			break;
		case 't':
			AddNewActor(new Target(position));
			++targetScore;
			break;
		}

		// x좌표 증가 처리
		++position.x;
	}

	delete[] data;

	fclose(file);
}

bool SokobanLevel::CanMove(const Wanted::Vector2& playerPosition, const Wanted::Vector2& nextPosition)
{
	// 레벨에 있는 박스 액터 모으기
	// 박스는 플레이어가 밀기 등 추가 처리가 필요하기 때문에 미리 찾아놓기
	std::vector<Actor*> boxes;
	for (Actor* const actor : actors)
	{
		if (actor->IsTypeOf<Box>())
		{
			boxes.emplace_back(actor);
			continue;
		}
	}

	// 이동하려는 위치에 박스가 있는지 확인
	Actor* boxActor = nullptr;
	for (Actor* const box : boxes)
	{
		if (box->GetPosition() == nextPosition)
		{
			boxActor = box;
			break;
		}
	}

	// 경우의 수 처리
	// nextPosition에 boxActor가 위치해있을 때 
	if (boxActor)
	{
		// 두 위치 사이에서 이동 방향 구하기(벡터의 뺄셈 활용), 이동 로직에서 두 벡터를 더한다는 것은 둘 중 하나는 위치이고 다른 하나는 벡터.
		Vector2 direction = nextPosition - playerPosition;
		Vector2 newPosition = boxActor->GetPosition() + direction;

		//for (Actor* const otherBox : boxes)
		//{
		//	if (otherBox == boxActor)
		//		continue;

		//	if (newPosition == otherBox->GetPosition())
		//		return false; // 플레이어가 박스를 밀었을 때의 newPosition에 박스가 있으면 cannot move
		//}

		for (Actor* const actor : actors)
		{
			if (newPosition == actor->GetPosition())
			{
				if (actor->IsTypeOf<Wall>() || actor->IsTypeOf<Box>() || actor->IsTypeOf<Player>())
				{
					return false;
				}
				if (actor->IsTypeOf<Ground>() || actor->IsTypeOf<Target>())
				{
					boxActor->SetPosition(newPosition);

					// 점수 확인
					isGameClear = CheckGameClear();

					return true;
				}
			}
		}
	}
	else { // nextPosition에 boxActor가 없을 때
		for (Actor* const actor : actors)
		{
			if (nextPosition == actor->GetPosition())
			{
				return actor->IsTypeOf<Wall>() ? false : true;
			}
		}
	}

	return false;
}

bool SokobanLevel::CheckGameClear()
{
	// 타겟 위에 있는 박스 수 체크
	int currentScore = 0;

	// 벡터에 박스 및 타겟 저장
	std::vector<Actor*> boxes;
	std::vector<Actor*> targets;

	// 레벨 액터 필터링
	for (Actor* const actor : actors)
	{
		if (actor->IsTypeOf<Box>())
		{
			boxes.emplace_back(actor);
			continue;
		}
		if (actor->IsTypeOf<Target>())
		{
			targets.emplace_back(actor);
		}
	}

	// 점수 확인(박스의 위치와 타겟의 위치 비교)
	for (Actor* const box : boxes)
	{
		for (Actor* const target : targets)
		{
			if (box->GetPosition() == target->GetPosition())
			{
				currentScore += 1;
			}
		}
	}

	// 목표 점수에 도달했는지 확인
	return currentScore == targetScore;
}