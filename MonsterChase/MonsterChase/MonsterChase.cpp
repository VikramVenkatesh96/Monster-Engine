// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>


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
		this->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
		CopyString(this->name, name, strlen(name));
		//this->name = name;
		genCharacterstics();
	}
	
	~Monster() {
		free(this->name);
	}

	static char* giveName() {											//Monster Name Generator
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
	void Move() {														//AI for monster: Moves horizontally or vertcally based on a random coin toss
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
	
	void CopyString(char * dest, char * src, unsigned int size) {
		for (unsigned int i = 0; i < size; ++i) {
			dest[i] = src[i];
		}
		dest[size] = '\0';
	}
};

char * TakeStringInput(char *);
void PrintPositions(int*, int*, char*, int, Monster**);
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
	char* player = (char *)malloc(sizeof(char));
	int playerPosX;
	int playerPosY;
	char input;
	bool isDead = false;

	std::cout << "\t\t\t\tMONSTER CHASE\n\n";
	std::cout << "Enter Player Name: ";
	player = TakeStringInput(player);
	playerPosX = rand() % GRIDX;
	playerPosY = rand() % GRIDY;
	
	std::cout << "\nEnter number of Monsters to spawn: ";
	std::cin >> numberOfMonsters;
	index = 0;
	
	while (index < numberOfMonsters) {
		char* temp = (char *)malloc(sizeof(char));
		std::cout << "\nEnter name for monster " << index + 1 << ": ";
		temp = TakeStringInput(temp);
		monsters[index] = new Monster(temp);
		free(temp);
		index++;
	}

	while (!isDead) {																						//Main game Loop
		isDead = CheckState(playerPosX, playerPosY, numberOfMonsters, monsters);
		PrintPositions(&playerPosX,&playerPosY,player,numberOfMonsters,monsters);
		PrintGUI();
		input = (char)_getch();
		input = (char)tolower(input);
		if (input == 'q')
			break;
		MovePlayer(input, &playerPosX, &playerPosY);
		MoveMonsters(numberOfMonsters,monsters);
		MonsterGen(&numberOfMonsters, monsters);
	}
	
	index = 0;																								//freeing memory here
	
	free(player);
	delete[] monsters;
}

char * TakeStringInput(char* string) {
	char c;
	int index = 0;
	while ((c = (char)_getche()) != '\r') {
		index++;
		string = (char*)realloc(string, sizeof(char) * (index + 1));
		string[index - 1] = c;
		string[index] = '\0';
	}
	return string;
}

bool CheckState(int X, int Y, int n, Monster** monsters) {													// Kill player if collided with monster
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


void PrintPositions(int *X, int *Y, char * player, int n, Monster** monster)
{
	std::cout << "\n" << player << " at " << "(" << *X << "," << *Y << ")";
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



void MonsterGen(int* numberOfMonsters, Monster** monsters) {
	int i = 0;
	int j = 1;
	int n = *numberOfMonsters;
	
	while (i < n) {																					//Check if Monster has expired
		if (monsters[i]->getLifeTime() == 0) {
			delete monsters[i];
			monsters[i] = new Monster(Monster::giveName());
			}
		i++;
	}
	
	i = 0;																							// Or check if any of the two monsters have collided and create a new monster
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
