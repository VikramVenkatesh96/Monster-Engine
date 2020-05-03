//Engine Headers
#include "Loader.h"
#include "MonsterEngine.h"


//STL Headers
#include <assert.h>

int CALLBACK WinMain(
	HINSTANCE,
	HINSTANCE,
	LPSTR,
	int 
)
{
	////Add all gameplay elements
	Loader::CreateObjectsFromFile("GameObjects.json");

	//Initialize all gameplay elements
	Loader::InitializeObjectsFromFile();

	//Run the app
	return MonsterEngine(800, 600, "MEngine").Run();
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
