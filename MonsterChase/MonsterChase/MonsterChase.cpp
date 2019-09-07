//Engine Headers
#include "MemoryManager.h"
#include "Point2D.h"
#include "GameObject.h"						//Not implemented yet 
//End Engine Headers

//Game Headers
#include "Monster.h"
//End Game Headers

// C/++ STL
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
//End STL

//Macros
#define MAXSIZE 64
#define GRIDX 256
#define GRIDY 256
#define PLAYERSPEED 1
//End Macros

//Globals
Point2D* LEFT = new Point2D(-PLAYERSPEED, 0);
Point2D* RIGHT = new Point2D(PLAYERSPEED, 0);
Point2D* UP = new Point2D(0, PLAYERSPEED);
Point2D* DOWN = new Point2D(0, -PLAYERSPEED);
//End Globals

//Function declarations
void PrintGameIntro();
void TakeStringInput(char*);
bool CheckState(Point2D*,int,Monster**);
void PrintPositions(char*,Point2D*,int, Monster**);
void PrintGUI();
void EnforceBoundaries(Point2D*);
void MovePlayer(char,Point2D*);
bool CheckBoundaries(Point2D*);
void MoveMonsters(int,Monster**);
void ManageMonsterGen(int*, Monster**);
void GenMonsterName(char*);
//End Function Declarations

int main() {
	//Intro Screen
	PrintGameIntro();

	//Player Initialization
	std::cout << "\nEnter Player name:";
	char* playerName = (char*)MemoryManager::AllocateMem(sizeof(char));
	TakeStringInput(playerName);
	Point2D* playerPos = new Point2D();

	//Monster Initialization
	int nMonsters;
	std::cout << "Enter Number of monsters to spawn:";
	std::cin >> nMonsters;
	Monster** monsters = (Monster**)MemoryManager::AllocateMem(sizeof(Monster*)*nMonsters);
	
	for (int i = 0; i < nMonsters; ++i) {
		monsters[i] = (Monster*) MemoryManager::AllocateMem(sizeof(Monster));
		monsters[i]->name = (char*)MemoryManager::AllocateMem(sizeof(char));
	}
	for (int i = 0; i < nMonsters; i++) {
		std::cout << "Enter name for Monster" << i + 1<< ":";
		TakeStringInput(monsters[i]->name);
		monsters[i]->lifeTime = rand() % 15;
		monsters[i]->position = new Point2D(rand() % GRIDX, rand() % GRIDY);
	}

	//GameLoop variables init
	bool isDead = false;
	char input;

	//Main Game Loop
	while (!isDead) {
		//system("CLS");
		isDead = CheckState(playerPos, nMonsters, monsters);
		PrintPositions(playerName,playerPos,nMonsters,monsters);
		PrintGUI();
		input = (char)_getch();
		input = (char)tolower(input);
		if (input == 'q')
			break;
		MovePlayer(input,playerPos);
		MoveMonsters(nMonsters,monsters);
		ManageMonsterGen(&nMonsters, monsters);
	}
	
	//Clear Game Memory
	
	//Local cleanup
	MemoryManager::FreeMem(playerName);
	delete playerPos;

	for (int i = 0; i < nMonsters; i++) {
		MemoryManager::FreeMem(monsters[i]->name);
		delete monsters[i]->position;
		MemoryManager::FreeMem(monsters[i]);
	}
	MemoryManager::FreeMem(monsters);

	//Global cleanup
	delete LEFT;
	delete RIGHT;
	delete UP;
	delete DOWN;

	int x;
	x = 5;
}

void PrintGameIntro()
{
	std::cout << "\t\t\t\t MONSTER CHASE\n\n";
}

void TakeStringInput(char* string) {
	char c ;
	int index = 0;
	while ((c = (char)_getche()) !='\r') {
		index++;
		string = (char*)MemoryManager::IncreaseMem(string, sizeof(char)*(index + 1));
		string[index - 1] = c;
		string[index] = '\0';
	}
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

void PrintPositions(char* playerName, Point2D* playerPos, int size, Monster** monsters)
{
	std::cout << "\n" << playerName << "at ";
	playerPos->PrintPoint();
	int index = 0;
	while (index < size) {
		std::cout << "\n";
		std::cout << "Monster " << monsters[index]->name << " alive untill " << monsters[index]->lifeTime << " at ";
		monsters[index]->position->PrintPoint();
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
	Point2D* toGo = new Point2D();
	while (index < size) {
		if (rand() % 2 == 0)
			toGo->x = 2 - (rand() % 4);
		else
			toGo->y = 2 - (rand() % 4);
		monsters[index]->Move(toGo);
		EnforceBoundaries(monsters[index]->position);
		index++;
	}
	
	//cleanup
	delete toGo;
}

void ManageMonsterGen(int* size, Monster** monsters)
{
	int n = *size;
	bool isColliding = false;

	for (int i = 0; i < n; i++) {
		if (monsters[i]->lifeTime == 0) {
			monsters = (Monster**)MemoryManager::DecreaseMem<Monster*>(monsters, n, i);
			*size--;
		}
	}

	n = *size;

	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (monsters[i]->position == monsters[j]->position) {
				isColliding = true;
				monsters = (Monster**)MemoryManager::IncreaseMem(monsters, sizeof(Monster*)*(n + 1));
				*size++;
				break;
			}
			if (isColliding)
				break;
		}

		if (isColliding) {
			//MonsterMen Init
			monsters[*size - 1] = (Monster*)MemoryManager::AllocateMem(sizeof(Monster));
			monsters[*size - 1]->name = (char*)MemoryManager::AllocateMem(sizeof(char)*2);

			//Monster Characterstics Gen
			GenMonsterName(monsters[i]->name);
			monsters[*size - 1]->lifeTime = rand() % 15;
			monsters[*size - 1]->position = new Point2D(rand() % GRIDX, rand() % GRIDY);
		}
	}
}

void GenMonsterName(char* name) {
	name[0] = (char)('A' + rand() % 26);
	name[1] = '\0';
}