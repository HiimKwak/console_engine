#include "TestLevel.h"
#include "Actor/Player.h"

TestLevel::TestLevel()
{
	// if (Wanted::Input::Get().GetKeyDown('Q'))
	// {
	// 
	// }
	AddNewActor(new Player());
}
