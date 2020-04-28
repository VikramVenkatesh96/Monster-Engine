#pragma once
#include "Graphics.h"
class Camera
{
public:
	DirectX::XMMATRIX GetMatrix() const;
	void ControlWindow();
	void Reset();

private:
	float r = 20.0f;
	float yaw = 0.0f;
};