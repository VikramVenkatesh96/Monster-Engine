//Engine Headers
#include "Point2D.h"
#include "Component.h"
#include "Script.h"
#include "GameObject.h"
#include "GameplayStatics.h"
#include "GamePlayStatics.cpp"
#include "Monster.h"
#include "PlayerCharacter.h"
#include "MainGameLoopVariables.h"

//Macros
#define MAXSIZE 64
#define GRIDX 256
#define GRIDY 256
#define PLAYERSPEED 1
//End Macros

//Gameplay scripts
void gamePlayStart() {

	PlayerCharacter* player = GamePlayStatics::FindObjectOfClass<PlayerCharacter>();
	Monster* monster = GamePlayStatics::FindObjectOfClass<Monster>();
	if (*player->position == *monster->position)
	{
		endUpdate = true;
	}
}
void gamePlayUpdate() {

	PlayerCharacter* player = GamePlayStatics::FindObjectOfClass<PlayerCharacter>();
	Monster* monster = GamePlayStatics::FindObjectOfClass<Monster>();
	if (*player->position == *monster->position)
	{
		endUpdate = true;
	}
}
int main() {
	//For dynamic updates on gameObjects list
	GameObject::SetGlobalGameObjectList(&gameObjects);
	
	//Drag in the player
	PlayerCharacter* player;
	player = new PlayerCharacter();

	//Drag in a monster
	Monster* monster;
	monster = new Monster(10,10);
	
	
	//Run Start Loop
	
	//Get the start node of the list all game objects
	ListNode<GameObject>* gameObjectIterator = gameObjects.start;
	while (gameObjectIterator != nullptr)
	{
		//Get the start node of all components in the gameObject
		ListNode<Component>* componentIterator = gameObjectIterator->value->GetAllComponents()->start;
		while (componentIterator != nullptr)
		{
			componentIterator->value->Start();
			componentIterator = componentIterator->next;
		}
		gameObjectIterator = gameObjectIterator->next;
	}
	gamePlayStart();

	//Next Run Update loop till end of MainGameLoop

	while (!endUpdate)
	{
		gamePlayUpdate();
		gameObjectIterator = gameObjects.start;
		while (gameObjectIterator != nullptr)
		{
			//Get the start node of all components in the gameObject
			ListNode<Component>* componentIterator = gameObjectIterator->value->GetAllComponents()->start;
			while (componentIterator != nullptr)
			{
				componentIterator->value->Update();
				componentIterator = componentIterator->next;
			}
			gameObjectIterator = gameObjectIterator->next;
		}
	}

	//Cleanup everything
	delete monster;
	delete player;
}


////Unit Test Code
//void Point2D_UnitTest()
//{
//	std::cout << "Running Unit Test....\n";
//	Point2D P1(1.0f, 0.0f);
//	Point2D P2(0.0f, 0.0f);
//
//	Point2D P3 = P1 + P2;
//	P3 = P1 - P2;
//	
//	Point2D P4 = P1 * 0.5f;
//	
//	Point2D P5 = P1 / 2.0f;
//	
//	Point2D P6 = -P4;
//
//	P6 *= 2.0f;
//	P5 /= 4.0f;
//	
//	P2 += P1;
//	P3 -= P1;
//
//
//	Point2D P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;
//
//	bool bArentEqual = P6 != P4;
//	std::cout << "\n bArentEqual: " << bArentEqual << std::endl;
//}