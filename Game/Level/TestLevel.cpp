#include <iostream>

#include "TestLevel.h"
#include "Actor/Player.h"

/*
* # = 벽
* . = 바닥
* p = 플레이어
* b = box
* t = 타겟
*/

TestLevel::TestLevel()
{
	//AddNewActor(new Player());
	LoadMap("Map.txt");
}

void TestLevel::LoadMap(const char* filename)
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

	// Test: 읽어온 데이터 임시로 출력
	std::cout << data;

	delete[] data;

	fclose(file);
}
