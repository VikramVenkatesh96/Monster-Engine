#include "Player.h"
#include "Controller.h"
#include "Input.h"
Player::Player()
{
	this->AddComponent(new Input(this));
	this->AddComponent(new Controller(this,ControllerType::Player));
}