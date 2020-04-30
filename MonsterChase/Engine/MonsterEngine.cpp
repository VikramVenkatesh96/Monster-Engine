#include "MonsterEngine.h"
#include "GameObject.h"
#include "Component.h"
#include "PhysicsSystem.h"
#include "MainGameLoopVariables.h"
#include "Sprite.h"

Keyboard* keyboard = nullptr;
Graphics* pGfx = nullptr;
std::vector<std::unique_ptr<Drawable>>* gDrawables = nullptr;

MonsterEngine::MonsterEngine(unsigned int width, unsigned int height, std::string appName)
	: WinApp(width, height, appName)
{
	//Set Graphics and drawables for renderer updates
	pGfx = GetGfxPtr();
	gDrawables = &drawables;

	//Set Keyboard for IO
	keyboard = GetKeyboard();

	//Run Start Loop
	StartLoop();
}

void MonsterEngine::UpdateFrame()
{
	const float dt = MarkTimer();

	GetGfxPtr()->BeginFrame(0,0,0.5f);
	GetGfxPtr()->SetCamera(camera.GetMatrix());

	/*if (keyboard->IsKeyPressed(VK_SPACE))
	{
		 sprites.push_back(new Sprite(L"Images\\2ab.png", 0.0f, 0.0f));
	}
	*/
	//Run Physics
	PhysicsSystem::Run(dt);

	//Run Update Loop for components
	UpdateLoop();

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

void MonsterEngine::StartLoop()
{
	std::vector<GameObject*>* gameObjects = GameObject::GetGlobalGameObjectList();
	for (unsigned int i = 0; i < gameObjects->size(); ++i)
	{
		GameObject* gameObject = gameObjects->at(i);
		std::vector<Component*>* components = gameObject->GetAllComponents();
		for (unsigned int j = 0; j < components->size(); ++j)
		{
			components->at(j)->Start();
		}
	}
}

void MonsterEngine::UpdateLoop()
{
	std::vector<GameObject*>* gameObjects = GameObject::GetGlobalGameObjectList();
	for (unsigned int i = 0; i < gameObjects->size(); ++i)
	{
		GameObject* gameObject = gameObjects->at(i);
		std::vector<Component*>* components = gameObject->GetAllComponents();
		for (unsigned int j = 0; j < components->size(); ++j)
		{
			components->at(j)->Update();
		}
		gameObject->Inspector();
	}
}


