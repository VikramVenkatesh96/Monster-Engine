//Engine Headers
#include "Point2D.h"
#include "Monster.h"
#include "Player.h"
#include "GameObject.h"	
#include "MainGameLoopVariables.h"


//MemDebugTool
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

//Macros
#define _CRTDBG_MAP_ALLOC
#define MAXSIZE 64
#define GRIDX 256
#define GRIDY 256
#define PLAYERSPEED 1
//End Macros

//Globals
Point2D* LEFT = DBG_NEW Point2D(-PLAYERSPEED, 0);
Point2D* RIGHT = DBG_NEW Point2D(PLAYERSPEED, 0);
Point2D* UP = DBG_NEW Point2D(0, PLAYERSPEED);
Point2D* DOWN = DBG_NEW Point2D(0, -PLAYERSPEED);
//End Globals

//Function declarations
//void PrintGameIntro();
//bool CheckState(Point2D*,int,Monster**);
//void PrintPositions(char*,/*Point2D*,*/int, Monster**);
//void PrintGUI();
//void EnforceBoundaries(Point2D*);
//void MovePlayer(char,Point2D*);
//bool CheckBoundaries(Point2D*);
//void MoveMonsters(int,Monster**);
//void ManageMonsterGen(int*, Monster**);
//void GenMonsterName(char*);
//void Point2D_UnitTest();
//End Function Declarations

int main() {
	//For dynamic updates on gameObjects list
	GameObject::SetGlobalGameObjectList(&gameObjects);
	Player* player = new Player();
	//Run Start Loop
	
	//Get the start node of the list all game objects
	ListNode<GameObject>* gameObjectIterator = gameObjects.start;
	while (gameObjectIterator != nullptr)
	{
		//Get the start node of all components in the gameObject
		ListNode<Component>* componentIterator = gameObjectIterator->value->GetAllComponents().start;
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
			ListNode<Component>* componentIterator = gameObjectIterator->value->GetAllComponents().start;
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

	_CrtDumpMemoryLeaks();
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