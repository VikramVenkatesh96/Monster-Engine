#include "Camera.h"
#include "IMGUI/imgui.h"

DirectX::XMMATRIX Camera::GetMatrix() const
{
	const auto pos = DirectX::XMVector3Transform(
		DirectX::XMVectorSet(0.0f, 0.0f, -r, 0.0f),
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f)
	);

	return DirectX::XMMatrixLookAtLH(
		pos, DirectX::XMVectorZero(),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	) * DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, yaw);

}

void Camera::ControlWindow()
{
	if (ImGui::Begin("Camera"))
	{
		ImGui::SliderFloat("Z-Distance", &r, 1.0f, 40.0f, "%.1f");
		ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f, "%.1f");

		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	ImGui::End();
}

void Camera::Reset()
{
	r = 20.0f;
	yaw = 0.0f;
}
