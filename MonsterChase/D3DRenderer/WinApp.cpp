#include "WinApp.h"
#include "Sheet.h"
#include "Surface.h"
#include "GDIPlusManager.h"
#include "IMGUI/imgui.h"
#include <memory>

GDIPlusManager gdipManager;

WinApp::WinApp(unsigned int width, unsigned int height, std::string appName)
	:width(width),
	 height(height),
	 appName(appName),
	win(width, height, appName.c_str())
{
	//Fill in drawables lists
	/*drawables.push_back(std::make_unique<Sheet>(win.Gfx(), L"Images\\SpaceOptimized.png", 12.0f, 16.0f, 0.0f, 0.01f));
	drawables.push_back(std::make_unique<Sheet>(win.Gfx(), L"Images\\Ring.png", 0.75f, 0.75f, 1.5f, -1.0f));*/

	win.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 1000.0f));
}

int WinApp::Run()
{
	while (true)
	{
		if (const auto eCode = Window::ProcessMessages())
		{
			return *eCode;
		}

		UpdateFrame();
	}
}

WinApp::~WinApp()
{
	gdipManager.~GDIPlusManager();
}

void WinApp::UpdateFrame()
{
}

