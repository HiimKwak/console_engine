#include <iostream>

#include "MenuLevel.h"
#include "Game/Game.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Render/Renderer.h"

MenuLevel::MenuLevel()
{
	items.emplace_back(new MenuItem(
		"Resume Game",
		[]() {
			Game::Get().ToggleMenu();
		}
	));
	items.emplace_back(new MenuItem(
		"Quit Game",
		[]() {
			Game::Get().Quit();
		}
	)
	);
}

MenuLevel::~MenuLevel()
{
	for (MenuItem*& item : items)
	{
		delete item;
		item = nullptr;
	}
	items.clear();
}

void MenuLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 입력 처리 (위아래 방향키, 엔터, ESC키)
	static int length = static_cast<int>(items.size());
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onSelected();
	}
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();

		currentIndex = 0;
	}
}

void MenuLevel::Draw()
{
	Renderer::Get().Submit("Sokoban Game", Vector2::Zero);

	for (int ix = 0; ix < static_cast<int>(items.size()); ++ix)
	{
		Color textColor =
			(ix == currentIndex) ? selectedColor : unselectedColor;

		Renderer::Get().Submit(items[ix]->text, Vector2(0, 2 + ix), textColor);
	}
}
