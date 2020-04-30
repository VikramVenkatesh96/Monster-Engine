#include "Component.h"
#include "GameObject.h"
#include "MainGameLoopVariables.h"
#include "IMGUI/imgui.h"

std::vector<GameObject*> GameObject::gameObjects;
GameObject::GameObject()
{
	position = new Point2D();
	gameObjects.push_back(this);
}

GameObject::~GameObject()
{
	RemoveAllComponents();
	//Delete this from gameObjects
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(),this), gameObjects.end());

}

void GameObject::Translate(Point2D toPosition) {

	*this->position = toPosition;
}

std::vector<Component*>* GameObject::GetAllComponents()
{
	return &components;
}

void GameObject::RemoveComponent(unsigned int index)
{
	components.erase(components.begin() + index);
}

void GameObject::RemoveAllComponents()
{
	components.clear();
}

void GameObject::Inspector()
{
	if (ImGui::Begin("Inspector"))
	{
		ImGui::Text("Position:");
		ImGui::Text("X: %.2f", position->x);
		ImGui::Text("Y: %.2f", position->y);
	}
	ImGui::End();

}

//void GameObject::SetGlobalGameObjectList(List<GameObject>& gameObjects)
//{
//	 gameObjects = globalGameObjectList;
//}

std::vector<GameObject*>* GameObject::GetGlobalGameObjectList()
{
	return &gameObjects;
}
