//Game Headers
//#include "Monster.h"

//Engine Headers
//#include "MemoryManager.h"
#include "FloatHelpers.h"
#include "MonsterEngine.h"
#include "Sprite.h"
//#include "Point2D.h"
//#include "Component.h"
//#include "GameObject.h"
//#include "PlayerCharacter.h"
#include "MainGameLoopVariables.h"

//STL Headers
#include <assert.h>

//Macros
#define MAXSIZE 64
#define GRIDX 256
#define GRIDY 256
#define PLAYERSPEED 1
//End Macros

bool FPUnitTest();

int CALLBACK WinMain(
	HINSTANCE,
	HINSTANCE,
	LPSTR,
	int 
)
{
	assert(FPUnitTest());

	//Add all gameplay elements
	Sprite* sprite;
	sprite = new Sprite(L"Images\\2ab.png", 0.0f, 0.0f);
	//Run the app
	return MonsterEngine(800, 600, "MEngine").Run();
}

bool FPUnitTest()
{
	//Checking for small comparisons
	float x = 0.15f;
	float y = 0.0f;
	for (unsigned int i = 1; i <= 15; ++i)
	{
		y += 0.01f;
	}
	
	if (!FloatHelpers::IsEqual(x, y))
	{
		return false;
	}
	//Checking for large comparisons
	volatile float z = 123456789.6969f;
	x *= z;
	y *= z;
	if (!FloatHelpers::IsEqual(x, y))
	{
		return false;
	}

	//Checking for zero comparison
	z -= 123456789.666f;
	if(!FloatHelpers::IsZero(z))
	{
		return false;
	}

	//Checking for NaN by 0/0
	x -= x;
	x /= z;
	if (!FloatHelpers::IsNaN(x))
	{
		return false;
	}
	
	//End test and passed!
	return true;
}

//int main() {
//	//Reserve memory from system for game heap
//	heapStart = HeapAlloc(GetProcessHeap(), 0, sizeOfHeap);
//	assert(heapStart);
//
//	//Init the Memory Manager
//	MemoryManager::Init(heapStart,sizeOfHeap,sizes,counts,count);
//
//	//For dynamic updates on gameObjects list
//	GameObject::SetGlobalGameObjectList(&gameObjects);
//	
//	//Initialize all gameplay elements
//
//	//Run Start Loop
//	
//	//Get the start node of the list all game objects
//	ListNode<GameObject>* gameObjectIterator = gameObjects.start;
//	while (gameObjectIterator != nullptr)
//	{
//		//Get the start node of all components in the gameObject
//		ListNode<Component>* componentIterator = gameObjectIterator->value->GetAllComponents()->start;
//		while (componentIterator != nullptr)
//		{
//			componentIterator->value->Start();
//			componentIterator = componentIterator->next;
//		}
//		gameObjectIterator = gameObjectIterator->next;
//	}
//
//	//Next Run Update loop till end of MainGameLoop
//
//	while (true)
//	{
//		gameObjectIterator = gameObjects.start;
//		while (gameObjectIterator != nullptr)
//		{
//			//Get the start node of all components in the gameObject
//			ListNode<Component>* componentIterator = gameObjectIterator->value->GetAllComponents()->start;
//			while (componentIterator != nullptr)
//			{
//				componentIterator->value->Update();
//				componentIterator = componentIterator->next;
//			}
//			gameObjectIterator = gameObjectIterator->next;
//		}
//	}
//	
//	//Destroy Memory Manager
//	MemoryManager::Destroy();
//	
//	//Free memory back to system
//	HeapFree(GetProcessHeap(), 0, const_cast<void*>(heapStart));
//}
