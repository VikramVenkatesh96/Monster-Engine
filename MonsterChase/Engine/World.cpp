#include "World.h"
#include "Drawable.h"
#include "GameObject.h"
#include "Keyboard.h"

Keyboard * World::keyboard = nullptr;
Graphics* World::pGfx = nullptr;
std::vector<SmartPtr<Drawable>>* World::gDrawables = nullptr;
std::vector<SmartPtr<GameObject>>* World::gameObjects = nullptr;
void* World::heapStart = nullptr;
const size_t World::sizeOfHeap = 16 * 1024 * 1024;
const unsigned int World::count = 3;
const unsigned int World::sizes[] = { 16, 32 ,96 };
const unsigned int  World::counts[] = { 100, 200, 400 };

World::World()
{
}

Keyboard * World::GetKeyboard()
{
	return keyboard;
}

Graphics * World::GetGraphics()
{
	return pGfx;
}

std::vector<SmartPtr<Drawable>>* World::GetDrawables()
{
	return gDrawables;
}

std::vector<SmartPtr<GameObject>>* World::GetGameObjects()
{
	return gameObjects;
}

void * World::GetHeapStart()
{
	return heapStart;
}

void World::InitializeGameObjects()
{
	for (unsigned int i = 0; i < gameObjects->size(); ++i)
	{
		gameObjects->at(i)->Initialize();
	}
}
