#include <iostream>
#include "Engine/Engine.h"
#include "Level/SokobanLevel.h"

using namespace Wanted;

int main()
{
	Wanted::Engine engine;
	engine.SetNewLevel(new SokobanLevel());
	engine.Run();
}