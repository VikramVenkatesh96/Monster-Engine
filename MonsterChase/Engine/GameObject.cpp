#include "Component.h"
#include "GameObject.h"
#include "MainGameLoopVariables.h"
#include "IMGUI/imgui.h"

List<GameObject>GameObject::globalGameObjectList = List<GameObject>();

GameObject::GameObject()
{
	position = new Point2D();
	components = new List<Component>();
	globalGameObjectList.Add(this);
}

GameObject::~GameObject()
{
	components->RemoveAll();
	globalGameObjectList.Remove(this);

}

void GameObject::Translate(Point2D toPosition) {

	*this->position = toPosition;
}

List<Component>* GameObject::GetAllComponents()
{
	return components;
}

void GameObject::RemoveComponent(unsigned int index)
{
	components->Remove(index);
}

void GameObject::RemoveAllComponents()
{
	components->RemoveAll();
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

List<GameObject>* GameObject::GetGlobalGameObjectList()
{
	return &globalGameObjectList;
}
