#include <iostream>

#include "SokobanLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

SokobanLevel::SokobanLevel()
{
	//AddNewActor(new Player());
	LoadMap("Map.txt");
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

	// 읽어온 문자열 분석(parsing)해서 추력
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

	return false;
}
