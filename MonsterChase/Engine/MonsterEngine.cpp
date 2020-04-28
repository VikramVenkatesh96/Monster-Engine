#include "MonsterEngine.h"
#include "GameObject.h"
#include "Component.h"
#include "MainGameLoopVariables.h"

Graphics* pGfx = nullptr;
std::vector<std::unique_ptr<Drawable>>* gDrawables = nullptr;

MonsterEngine::MonsterEngine(unsigned int width, unsigned int height, std::string appName)
	: WinApp(width, height, appName)
{
	//Set Graphics and drawables for renderer updates
	pGfx = GetGfxPtr();
	gDrawables = &drawables;
	//Run Start Loop
	List<GameObject>* gameObjects = GameObject::GetGlobalGameObjectList();
	//Get the start node of the list all game objects
	ListNode<GameObject>* gameObjectIterator = gameObjects->start;
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
}

void MonsterEngine::UpdateFrame()
{
	const float dt = MarkTimer();

	GetGfxPtr()->BeginFrame(0,0,0.5f);
	GetGfxPtr()->SetCamera(camera.GetMatrix());

	List<GameObject>* gameObjects = GameObject::GetGlobalGameObjectList();
	//Run the Update Loop for each Gameobject and its Component
	ListNode<GameObject>* gameObjectIterator = gameObjects->start;
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

	//Draw all drawables
	for (auto& d : drawables)
	{
		d->Update(dt);
		d->Draw(*GetGfxPtr());
	}
	
	//Display Camera control GUI
	camera.ControlWindow();

	GetGfxPtr()->EndFrame();
}
