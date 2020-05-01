#pragma once
#include "Pointers.h"
#include <algorithm>
#include <vector>

class Keyboard;
class GameObject;
class Graphics;
class Drawable;
class World
{
public:
	World();
	static Keyboard* GetKeyboard();
	static Graphics* GetGraphics();
	static inline void SetGraphics(Graphics* i_pGfx)
	{
		pGfx = i_pGfx;
	}
	static inline void SetKeyBoard(Keyboard* i_kbd)
	{
		keyboard = i_kbd;
	}
	static inline void SetDrawables(std::vector<SmartPtr<Drawable>>* i_drawables)
	{
		gDrawables = i_drawables;
	}
	static std::vector<SmartPtr<Drawable>>* GetDrawables();
	static std::vector<SmartPtr<GameObject>>* GetGameObjects();
	static void* GetHeapStart();

	static inline void AddGameObject(SmartPtr<GameObject> object)
	{
		gameObjects->push_back(object);
	}

	static inline void RemoveGameObject(SmartPtr<GameObject> object)
	{
		gameObjects->erase(std::remove(gameObjects->begin(), gameObjects->end(), object), gameObjects->end());
	}

	static void InitializeGameObjects();

private:
#pragma region IO
	static Keyboard * keyboard;
#pragma endregion

#pragma region Rendering Variables
	static Graphics* pGfx;
	static std::vector<SmartPtr<Drawable>>* gDrawables;
#pragma endregion

#pragma region EngineRefs
	static std::vector<SmartPtr<GameObject>>* gameObjects;
#pragma endregion

#pragma region MemoryManager variables
	//Heap start and size
	static void* heapStart;
	static const size_t sizeOfHeap;

	//Fixed size allocator sizes and counts
	static const unsigned int count;
	//This has to be in ascending order
	static const unsigned int sizes[];
	static const unsigned int counts[];

#pragma endregion
};


