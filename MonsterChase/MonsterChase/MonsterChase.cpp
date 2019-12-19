//Engine Headers
#include "Point2D.h"
#include "Component.h"
#include "GameObject.h"
#include "Monster.h"
#include "PlayerCharacter.h"
#include "MainGameLoopVariables.h"

//Macros
#define MAXSIZE 64
#define GRIDX 256
#define GRIDY 256
#define PLAYERSPEED 1
//End Macros


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

	//Next Run Update loop till end of MainGameLoop

	while (true)
	{
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
	////Point2D UnitTest
	////Point2D_UnitTest();

	////Intro Screen
	//PrintGameIntro();

	////Player Initialization
	//std::cout << "\nEnter Player name:";
	//char* playerName = (char*)MemoryManager::AllocateMem(sizeof(char));
	//IO::TakeStringInput(playerName);
	//Point2D* playerPos = DBG_NEW Point2D();

	////Monster Initialization
	//int nMonsters;
	//std::cout << "Enter Number of monsters to spawn:";
	//std::cin >> nMonsters;
	//Monster** monsters = (Monster**)MemoryManager::AllocateMem(sizeof(Monster*)*nMonsters);
	//
	//for (int i = 0; i < nMonsters; ++i) {
	//	monsters[i] = new Monster(GRIDX, GRIDY);
	//	std::cout << "Enter name for Monster" << i + 1 << ":";
	//	IO::TakeStringInput(monsters[i]->name);
	//}

	////GameLoop variables init
	//bool isDead = false;
	//bool isWin = false;
	//char input;

	//monsters[1]->lifeTime = 1;

	////Main Game Loop

	//while (!isDead && !isWin) {
	//	//system("CLS");
	//	isDead = CheckState(playerPos, nMonsters, monsters);
	//	PrintPositions(playerName,/*playerPos,*/nMonsters,monsters);
	//	PrintGUI();
	//	input = (char)_getch();
	//	input = (char)tolower(input);
	//	if (input == 'q')
	//		break;
	//	MovePlayer(input,playerPos);
	//	MoveMonsters(nMonsters,monsters);
	//	ManageMonsterGen(&nMonsters, monsters);
	//	if (nMonsters == 0)
	//		isWin = true;
	//}
	//
	//if (isWin) {
	//	std::cout << "\nYou Win!!";
	//	nMonsters = 1;
	//}
	//
	////Clear Game Memory
	////Local cleanup
	//MemoryManager::FreeMem(playerName);
	//delete playerPos;

	//for (int i = 0; i < nMonsters; i++) {
	//	delete monsters[i];
	//}

	////Global cleanup
	//delete LEFT;
	//delete RIGHT;
	//delete UP;
	//delete DOWN;
	int x ;
	x = 5;
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