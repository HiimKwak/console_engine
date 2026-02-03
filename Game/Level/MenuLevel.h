#pragma once

#include <vector>

#include "Level/Level.h"
#include "Math/Color.h"

using namespace Wanted;

struct MenuItem {
	char* text = nullptr;

	using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected) : onSelected(onSelected) {
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}

	~MenuItem()
	{
		if (text)
		{
			delete[] text;
			text = nullptr;
		}
	}

	OnSelected onSelected = nullptr;
};

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

	// 이벤트 함수 오버라이드
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	// 현재 활성화된 메뉴 인덱스
	int currentIndex = 0;

	Color selectedColor = Color::Green;
	Color unselectedColor = Color::White;

	std::vector<MenuItem*> items;
};

