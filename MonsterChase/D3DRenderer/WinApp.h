#pragma once
#include "Window.h"
#include "Timer.h"
#include "IMGUIManager.h"
#include "Camera.h"
#include <vector>

class WinApp
{
public:
	WinApp();
	int Run();
	~WinApp();
private:
	void UpdateFrame();
private:
	bool show_demo_window = true;
	IMGUIManager GUIManager;
	Window win;
	Timer timer;
	Camera camera;
	std::vector<std::unique_ptr<class Drawable>> drawables;
};
