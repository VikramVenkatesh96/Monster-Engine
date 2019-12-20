#include "PlayerCharacter.h"
#include "Controller.h"
#include "Input.h"
#include "Script.h"
#include <iostream>
#include <stdlib.h>
#include <functional>

PlayerCharacter::PlayerCharacter()
{
	Controller* controllerComp = new Controller(this, ControllerType::Player);
	std::function<void()> startFunc = std::bind(&PlayerCharacter::ScriptStart, this);
	std::function<void()> updateFunc = std::bind(&PlayerCharacter::ScriptUpdate, this);
	Script* script = new Script(this, startFunc, updateFunc);
	Input* inputComponent = new Input(this);
	this->AddComponent(inputComponent);
	this->AddComponent(controllerComp);
	this->AddComponent(script);
}

void PlayerCharacter::ScriptStart()
{
	std::cout << "Player Initialized with position: ";
	position->PrintPoint();
	std::cout << std::endl;
}

void PlayerCharacter::ScriptUpdate()
{
	system("CLS");
	std::cout << "Player at :";
	position->PrintPoint();
	std::cout << std::endl;
}