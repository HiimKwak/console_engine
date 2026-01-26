#include <iostream>
#include "TestActor.h"

void TestActor::BeginPlay()
{
	// C++는 부모함수 가리키는 포인터가 없음
	Actor::BeginPlay();

	std::cout << "TestActor::BeginPlay().\n";
}

void TestActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	std::cout 
		<< "TestActor::Tick(). deltaTime: " << deltaTime 
		<< ", FPS: " << (1.f / deltaTime) 
		<< std::endl;
}

void TestActor::Draw()
{
	Actor::Draw();
}
