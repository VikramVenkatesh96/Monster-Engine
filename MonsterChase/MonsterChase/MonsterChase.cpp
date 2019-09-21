//Engine Headers
#include "MemoryManager.h"
#include "Point2D.h"
#include "GameObject.h"	//Not implemented yet
#include "IO.h"
//End Engine Headers

//Game Headers
#include "Monster.h"
//End Game Headers

// C/++ STL
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <crtdbg.h>
//End STL

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
void PrintGameIntro();
bool CheckState(Point2D*,int,Monster**);
void PrintPositions(char*,/*Point2D*,*/int, Monster**);
void PrintGUI();
void EnforceBoundaries(Point2D*);
void MovePlayer(char,Point2D*);
bool CheckBoundaries(Point2D*);
void MoveMonsters(int,Monster**);
void ManageMonsterGen(int*, Monster**);
void GenMonsterName(char*);
void Point2D_UnitTest();
//End Function Declarations

int main() {
	//Point2D UnitTest
	Point2D_UnitTest();

	//Intro Screen
	PrintGameIntro();

	//Player Initialization
	std::cout << "\nEnter Player name:";
	char* playerName = (char*)MemoryManager::AllocateMem(sizeof(char));
	IO::TakeStringInput(playerName);
	Point2D* playerPos = DBG_NEW Point2D();

	//Monster Initialization
	int nMonsters;
	std::cout << "Enter Number of monsters to spawn:";
	std::cin >> nMonsters;
	Monster** monsters = (Monster**)MemoryManager::AllocateMem(sizeof(Monster*)*nMonsters);
	
	for (int i = 0; i < nMonsters; ++i) {
		monsters[i] = new Monster(GRIDX, GRIDY);
		std::cout << "Enter name for Monster" << i + 1 << ":";
		IO::TakeStringInput(monsters[i]->name);
	}

	//GameLoop variables init
	bool isDead = false;
	bool isWin = false;
	char input;

	monsters[1]->lifeTime = 1;

	//Main Game Loop
	while (!isDead && !isWin) {
		//system("CLS");
		isDead = CheckState(playerPos, nMonsters, monsters);
		PrintPositions(playerName,/*playerPos,*/nMonsters,monsters);
		PrintGUI();
		input = (char)_getch();
		input = (char)tolower(input);
		if (input == 'q')
			break;
		MovePlayer(input,playerPos);
		MoveMonsters(nMonsters,monsters);
		ManageMonsterGen(&nMonsters, monsters);
		if (nMonsters == 0)
			isWin = true;
	}
	
	if (isWin) {
		std::cout << "\nYou Win!!";
		nMonsters = 1;
	}
	
	//Clear Game Memory
	//Local cleanup
	MemoryManager::FreeMem(playerName);
	delete playerPos;

	for (int i = 0; i < nMonsters; i++) {
		delete monsters[i];
	}

	//Global cleanup
	delete LEFT;
	delete RIGHT;
	delete UP;
	delete DOWN;

	_CrtDumpMemoryLeaks();
}

void PrintGameIntro()
{
	std::cout << "\t\t\t\t MONSTER CHASE\n\n";
}


bool CheckState(Point2D* playerPos, int size, Monster** monsters)
{	
	int index = 0;
	bool isDead = false;
	while (index < size) {
		if (playerPos == monsters[index]->position) {
			isDead = true;
			std::cout << "\nYou are Dead!\n";
		}
		index++;
	}
	return isDead;
}

void PrintPositions(char* playerName,/* Point2D* playerPos,*/ int size, Monster** monsters)
{	
	std::cout << "\n" << playerName << " at ";
	//playerPos->PrintPoint();
	int index = 0;
	while (index < size) {
		std::cout << "\n";
		std::cout << "Monster " << monsters[index]->name << " alive untill " << monsters[index]->lifeTime << " at ";
		//monsters[index]->position->PrintPoint();
		index++;
	}
}

void PrintGUI() {
	std::cout << "\nUse W,A,S,D to move up,left,down,right respectively:  ";
}

void EnforceBoundaries(Point2D* position) {
	if (position->x < 0)
		position->x = 0;
	else if (position->x > GRIDX)
		position->x = GRIDX;
	
	if (position->y < 0)
		position->y = 0;
	else if (position->y > GRIDY)
		position->y = GRIDY;
}

void MovePlayer(char input, Point2D* playerPos)
{
	if ((input == 'w') || (input == 'a') || (input == 's') || (input == 'd')) {	
		if (playerPos->x < 0)
			playerPos->x = 0;
		else if (playerPos->x > GRIDX)
			playerPos->x = GRIDX;
		else if (input == 'a')
			*playerPos = *playerPos + *LEFT;
		else if (input == 'd')
			*playerPos = *playerPos + *RIGHT;

		if (playerPos->y < 0)
			playerPos->x = 0;
		else if (playerPos->y > GRIDY)
			playerPos->x = GRIDY;
		else if (input == 'w')
			*playerPos = *playerPos + *UP;
		else if (input == 's')
			*playerPos = *playerPos + *DOWN;
	}
	else
		std::cout << "\nInvalid Input";
	
}

void MoveMonsters(int size, Monster** monsters)
{
	int index = 0;
	Point2D* toGo = DBG_NEW Point2D();
	while (index < size) {
		//init toGo
		toGo->x = 0;
		toGo->y = 0;
		if (rand() % 2 == 0)
			toGo->x = static_cast <float> ( 2 - (rand() % 4));
		else
			toGo->y = static_cast <float> (2 - (rand() % 4));
		
		monsters[index]->Move(toGo);
		EnforceBoundaries(monsters[index]->position);
		index++;
	}
	delete toGo;
}

void ManageMonsterGen(int* size, Monster** monsters)
{
	int n = *size;
	bool isColliding = false;
	//Check if a Monster has expired
	for (int i = 0; i < n; i++) {
		if (monsters[i]->lifeTime == 0) {
			if (n != 1) {
				monsters = (Monster**)MemoryManager::DecreaseMem<Monster*>(monsters, n, i);
			}
			*size = *size - 1;
		}
	}
	//No collisions or generating required if we have less than 2 monsters
	if (*size < 2)
		return;

	n = *size;

	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (monsters[i]->position == monsters[j]->position) {
				isColliding = true;
				monsters = (Monster**)MemoryManager::IncreaseMem(monsters, sizeof(Monster*)*(n + 1));
				*size = *size + 1;
				break;
			}
			if (isColliding)
				break;
		}

		if (isColliding) {
			//MonsterMen Init
			monsters[*size - 1] = DBG_NEW Monster(GRIDX,GRIDY);

			//Monster Characterstics Gen
			GenMonsterName(monsters[i]->name);
		}
	}
}

void GenMonsterName(char* name) {
	name[0] = (char)('A' + rand() % 26);
	name[1] = '\0';
}

//Unit Test Code
void Point2D_UnitTest()
{
	std::cout << "Running Unit Test....\n";
	Point2D P1(1.0f, 0.0f);
	Point2D P2(0.0f, 0.0f);

	Point2D P3 = P1 + P2;
	P3 = P1 - P2;
	
	Point2D P4 = P1 * 0.5f;
	
	Point2D P5 = P1 / 2.0f;
	
	Point2D P6 = -P4;

	P6 *= 2.0f;
	P5 /= 4.0f;
	
	P2 += P1;
	P3 -= P1;


	Point2D P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;

	bool bArentEqual = P6 != P4;
	std::cout << "\n bArentEqual: " << bArentEqual << std::endl;
}