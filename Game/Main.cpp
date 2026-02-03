#include <iostream>

#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/SokobanLevel.h"

using namespace Wanted;

int main()
{
	/*Game game;
	game.Run();*/

	const int width = 3;
	const int height = 3;
	CHAR_INFO charArray[width * height] = {};

	charArray[2 * width + 1].Char.AsciiChar = 'P';
	charArray[2 * width + 1].Attributes = FOREGROUND_GREEN;

	charArray[0 * width + 1].Char.AsciiChar = '#';
	charArray[0 * width + 1].Attributes = FOREGROUND_RED;

	COORD position = {};
	COORD screenSize;
	screenSize.X = 3;
	screenSize.Y = 3;

	SMALL_RECT writeRegion{
		0, 0, static_cast<short>(width), static_cast<short>(height)
	};

	// 문자 배열을 한번에 콘솔로 넘겨 그릴 때 사용하는 함수
	// 인자로 1차원 배열(char CHAR_INFO)을 넘기지만 콘솔은 2차원 배열처럼 렌더됨
	WriteConsoleOutputA
	(
		GetStdHandle(STD_OUTPUT_HANDLE),
		charArray,
		screenSize,
		position,
		&writeRegion
	);

	// 창 하나 이미지 하나에 핸들 2개를 돌려쓰기
	//CreateConsoleScreenBuffer()
	//SetConsoleActiveScreenBuffer()

	std::cin.get();
}