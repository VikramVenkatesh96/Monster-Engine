#pragma once
#include "Window.h"
#include "Timer.h"
#include "IMGUIManager.h"
#include "Camera.h"
#include "Sheet.h"
#include <vector>

class WinApp
{
public:
	WinApp(unsigned int width, unsigned int height, std::string appName);
	~WinApp();
	int Run();

	inline unsigned int GetWidth()
	{
		return width;
	}

	inline unsigned int GetHeight()
	{
		return height;
	}


	inline void SetWidth(unsigned int i_width)
	{
		width = i_width;
	}

	inline void SetHeight(unsigned int i_height)
	{
		height = i_height;
	}

	inline Graphics* GetGfxPtr()
	{
		return win.p_Gfx();
	};
	inline float MarkTimer()
	{
		return timer.Mark();
	}
	
	inline Keyboard* GetKeyboard()
	{
		return &win.kbd;
	}
protected:
	virtual void UpdateFrame();

private:
	unsigned int width;
	unsigned int height;
	std::string appName;
	bool show_demo_window = true;
	IMGUIManager GUIManager;
	Window win;
	Timer timer;
};
