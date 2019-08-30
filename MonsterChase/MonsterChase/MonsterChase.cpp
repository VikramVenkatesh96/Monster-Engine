// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define MAXSIZE 32
#define MAXNUMBER 64
#define GRIDX 256
#define GRIDY 256
#define PLAYERSPEED 1


class Monster {

private:

	char* name;
	int lifeTime;
	int posX;
	int posY;
	int moveAI;
public:	
	Monster(char* name) {
		this->name = name;
		genCharacterstics();
	}

	static char* giveName() {											//Random input
		std::string temp = "Monster ";
		char c = 'A' + rand() % 26;
		temp.append(1,c);
		char* name = &temp[0];
		return name;
	}
	void genCharacterstics() {
		this->lifeTime = rand() % 15 + 1;
		this->posX = rand() % GRIDX;
		this->posY = rand() % GRIDY;
		this->moveAI = rand() % 4;
	}
	char* getName() {
		return name;
	}
	int getLifeTime() {
		return lifeTime;
	}
	int getX() {
		return posX;
	}
	int getY() {
		return posY;
	}
	void Move() {
		if (moveAI == 0) {
			if (posY >= GRIDY) {	
				moveAI = 1;
			}
			else {
				posY++;
			}
		}
		else if (moveAI == 1) {
			if (posY <= 0) {
				moveAI = 0;
			}
			else {
				posY--;
			}
		}
		else if (moveAI == 2) {
			if (posX >= GRIDX) {
				moveAI = 3;
			}
			else {
				posX++;
			}
		}
		else {
			if (posX <= 0) {
				moveAI = 2;
			}
			else {
				posX--;
			}
		}
		lifeTime--;
	}
	
	void DeleteMonster() {
		delete[] name;
	}
	
};


void PrintPositions(int*, int*, int, Monster**);
void PrintGUI();
void MovePlayer(char, int*, int*);
void MoveMonsters(int, Monster**);
bool CheckState(int, int, int, Monster**);
void MonsterGen(int*, Monster**);

int main()
{
	Monster **monsters = new Monster*[MAXNUMBER];
	int index;
	int numberOfMonsters;
	char* player = new char[MAXSIZE];
	int playerPosX;
	int playerPosY;
	char input;
	bool isDead = false;

	std::cout << "\t\t\t\tMONSTER CHASE\n\n";
	std::cout << "Enter Player Name: ";
	std::cin >> player;
	playerPosX = rand() % GRIDX;
	playerPosY = rand() % GRIDY;
	
	std::cout << "\nEnter number of Monsters to spawn: ";
	std::cin >> numberOfMonsters;
	index = 0;
	
	while (index < numberOfMonsters) {
		char* temp = new char[MAXSIZE];
		std::cout << "\nEnter name for monster " << index + 1 << ": ";
		std::cin >> temp;
		monsters[index] = new Monster(temp);
		index++;
	}

	while (!isDead) {
		isDead = CheckState(playerPosX, playerPosY, numberOfMonsters, monsters);
		PrintPositions(&playerPosX,&playerPosY,numberOfMonsters,monsters);
		PrintGUI();
		input = (char)_getch();
		input = (char)tolower(input);
		if (input == 'q')
			break;
		MovePlayer(input, &playerPosX, &playerPosY);
		MoveMonsters(numberOfMonsters,monsters);
		MonsterGen(&numberOfMonsters, monsters);
	}
	
	index = 0;
	delete[] player;
	while (index < numberOfMonsters) {
		delete[] monsters[index];
		index++;
	}
	delete[] monsters;
	
	int x = 0;
	x = 5;
}

void PrintPositions(int *X, int *Y, int n, Monster** monster)
{
	std::cout << "\nPlayer at " << "(" << *X << "," << *Y << ")";
	int index = 0;
	while (index < n) {
		std::cout << "\n";
		std::cout << monster[index]->getName() << " alive untill " << monster[index]->getLifeTime()
			<< " at (" << monster[index]->getX() << "," << monster[index]->getY() << ")";
		index++;
	}
}

void PrintGUI() {
	std::cout << "\nUse W,A,S,D to move UP,LEFT,DOWN,RIGHT: ";
}

void MovePlayer(char input, int* X, int* Y) {
	
	if ((input == 'w') || (input == 'a') || (input == 's') || (input == 'd')) {
		
		if (*X <= 0) {
			*X = 0;
		}
		else if (*X >= GRIDX) {
			*X = GRIDX;
		}
		else if (input == 'a') {
			*X -= PLAYERSPEED;
		}
		else if (input == 'd') {
			*X += PLAYERSPEED;
		}

		if (*Y <= 0) {
			*Y = 0;
		}
		else if (*Y >= GRIDY) {
			*Y = GRIDY;
		}
		else if (input == 'w') {
			*Y += PLAYERSPEED;
		}
		else if (input == 's') {
			*Y -= PLAYERSPEED;
		}
	}
	
	else {
		std::cout << "Invalid input!\n";
	}

}

void MoveMonsters(int n, Monster** monsters) {
	int index = 0;
	while (index < n) {
		monsters[index]->Move();
		index++;
	}
}

bool CheckState(int X, int Y, int n, Monster** monsters) {
	int index = 0;
	bool isDead = false;
	while (index < n) {
		if (X == monsters[index]->getX() && Y == monsters[index]->getY()) {
			isDead = true;
			std::cout << "\nYou are Dead!\n";
		}
		index++;
	}
	return isDead;
}


void MonsterGen(int* numberOfMonsters, Monster** monsters) {
	int i = 0;
	int j = 1;
	int n = *numberOfMonsters;
	
	while (i < n) {
		if (monsters[i]->getLifeTime() == 0) {
			delete monsters[i];
			monsters[i] = new Monster(Monster::giveName());
			}
		i++;
	}
	
	i = 0;
	while (i < n-1) {
		while (j < n) {
			if (monsters[i]->getX() == monsters[j]->getX() && monsters[i]->getY() == monsters[j]->getY()) {
				if (n < MAXNUMBER) {
					monsters[n] = new Monster(Monster::giveName());
					*numberOfMonsters++;	
				}
			}
			j++;
		}
		i++;
	}

}

//#include<iostream>
//
//
//
//class Monster {
//private:
//	char* name;
//	int lifeTime;
//	int posX;
//	int posY;
//	int moveAI;
//
//public:
//	Monster(char* name) {
//		this->name = name;
//		GenCharacterstics();
//	}
//	void GenCharacterstics() {
//		this->lifeTime = rand() % 15 + 1;
//		this->posX = rand() % GRIDX;
//		this->posY = rand() % GRIDY;
//		this->moveAI = rand() % 4;
//		}
//	char* getName() {
//		return name;
//	}
//};
//
//int main() {
//	int n;
//	int index = 0;
//	std::cout << "Enter number of monsters";
//	std::cin >> n;
//	Monster** monsters = new Monster*[MAXNUMBER];
//	while (index < n)
//	{
//		char* temp = new char[MAXSIZE];
//		std::cin >> temp;
//		monsters[index] = new Monster(temp);
//		index++;
//	}
//	index = 0;
//	while (index < n)
//	{
//		std::cout << monsters[index] << " " << monsters[index]->getName()<<"/n";
//		index++;
//	}
//	
//	delete[] monsters;
//	
//	int x = 0;
//	x = 5;
//}
//#include<iostream>
//#include<string.h>
//
//int main() {
//	std::string temp = "Monster ";
//	char c = 'A' + rand() % 26;
//	temp.append(1,c);
//	char* name = &temp[0];
//	std::cout << name;
//}