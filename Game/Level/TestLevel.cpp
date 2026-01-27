#include "TestLevel.h"
#include "Actor/TestActor.h"

TestLevel::TestLevel()
{
	// if (Wanted::Input::Get().GetKeyDown('Q'))
	// {
	// 
	// }
	AddNewActor(new TestActor());
}
