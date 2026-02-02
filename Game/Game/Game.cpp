#include <iostream>

#include "Game.h"
#include "Level/SokobanLevel.h"
#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	// 레벨 생성 및 배열 추가
	levels.emplace_back(new SokobanLevel());
	levels.emplace_back(new MenuLevel());

	// 시작 레벨 설정
	state = State::GamePlay;

	// 게임 시작 시 활성화할 레벨 결정
	mainLevel = levels[State::GamePlay];
}

Game::~Game()
{
	// 중복 제거 방지
	mainLevel = nullptr;

	for (Level*& level : levels) // index로 반복문 돌리거나 2차포인터로 접근하기
	{
		delete level;
		level = nullptr;
	}

	// 배열 정리
	levels.clear();
}

void Game::ToggleMenu()
{
	// 화면 지우기
	system("cls"); // 콘솔 명령어 실행 함수

	// 변경할 인덱스 계산
	// 현재 활성 레벨 인덱스 토글
	int stateIndex = (int)state;
	int nextState = 1 - stateIndex; // 마법의 공식 1-x(OneMinus) - 림라이트 기초
	state = (State)nextState;

	// 메인레벨 변경
	mainLevel = levels[static_cast<int>(state)]
}

Game& Game::Get()
{
	if (!instance)
	{
		std::cerr << "Game:Get() - instance is null\n";
		__debugbreak();
	}

	return *instance;
}