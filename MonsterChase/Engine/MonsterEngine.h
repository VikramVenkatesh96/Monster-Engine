//This is the interface connecting the D3DRenderer WinApp to the Engine
#pragma once
#include "WinApp.h"
#include "Pointers.h"

class MonsterEngine : public WinApp
{
public:
	MonsterEngine(unsigned int width, unsigned int height, std::string appName);

protected:
	void UpdateFrame() override;

private:
	void StartLoop();
	void UpdateLoop();

private:
	Camera camera;
	std::vector<SmartPtr<class Drawable>> drawables;
};

