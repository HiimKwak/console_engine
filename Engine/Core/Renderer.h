#pragma once

#include <iostream>
#include <vector>

#include "Util/Util.h"

namespace Wanted
{
	// DLL 내부에서만 사용하므로 WANTED_API 사용 안함
	class Renderer
	{
	public:
		// 그리기,
		static void Draw(const char image)
		{
			std::cout << image;
		}

		// 위치 설정, 그리기 한 번에 처리
		static void Draw(const Vector2& position, const char image)
		{
			Util::SetConsolePosition(position);
			Draw(image);
		}

		// 위치, 색상, 그리기 한 번에 처리
		static void Draw(const Vector2& position, Color color, const char image)
		{
			Util::SetConsolePosition(position);
			Util::SetConsoleTextColor(color);
			Draw(image);

			// 색상 원복
			Util::SetConsoleTextColor(Color::White);
		}
	};
}