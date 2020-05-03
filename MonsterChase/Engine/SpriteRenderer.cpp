#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Sheet.h"
#include"World.h"


SpriteRenderer::SpriteRenderer(GameObject& root, std::wstring i_fileName):
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
			gameObject.position->x,
			gameObject.position->y,
			1.0f, 1.0f,
			0.0f));
	
	World::GetDrawables()->push_back(sheet);

}

void SpriteRenderer::Update()
{
	//Change parameters in sheet according to transform
	sheet->SetPosition(gameObject.position->x, gameObject.position->y);
}
