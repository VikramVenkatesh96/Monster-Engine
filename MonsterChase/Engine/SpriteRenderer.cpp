#include "SpriteRenderer.h"
#include "GameObject.h"
#include"World.h"

SpriteRenderer::SpriteRenderer(SmartPtr<GameObject>root, std::wstring i_fileName):
	Component(root)
{
	fileName = i_fileName;
}

void SpriteRenderer::Start()
{
	sheet = SmartPtr<Sheet>(
			new Sheet(
			*World::GetGraphics(),
			fileName,
			gameObject.Acquire()->position->x,
			gameObject.Acquire()->position->y,
			1.0f, 1.0f,
			0.0f));
	
	World::GetDrawables()->push_back(sheet);

}

void SpriteRenderer::Update()
{
	//Change parameters in sheet according to transform
	//sheet->SetPosition(gameObject.Acquire()->position->x, gameObject.Acquire()->position->y);
}
