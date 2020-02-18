#include "IMGUIManager.h"
#include "ImGUI/imgui.h"


IMGUIManager::IMGUIManager()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
}


IMGUIManager::~IMGUIManager()
{
	ImGui::DestroyContext();
}
