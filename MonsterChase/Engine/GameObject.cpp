#include "Component.h"
#include "GameObject.h"
#include "IMGUI/imgui.h"

GameObject::GameObject()
{
	position = new Point2D();
}

GameObject::~GameObject()
{
	delete position;
}

void GameObject::Initialize()
{
}

void GameObject::Translate(Point2D toPosition) {

	*this->position = toPosition;
}

SmartPtr<Component> GameObject::GetAtIndex(unsigned int index)
{
	return components.at(index);
}

std::vector<SmartPtr<Component>>* GameObject::GetAllComponents()
{
	return &components;
}

void GameObject::RemoveComponent(unsigned int index)
{
	components.erase(components.begin() + index);
}

void GameObject::RemoveAllComponents()
{
	for (unsigned int i = 0; i < components.size(); ++i)
	{
		components.erase(components.begin() + i);
	}
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

