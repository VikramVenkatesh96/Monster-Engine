#include "SpriteRenderer.h"
#include "Sheet.h"
#include "GameObject.h"
#include "MainGameLoopVariables.h"

SpriteRenderer::SpriteRenderer(GameObject * root, std::wstring i_fileName)
{
	gameObject = root;
	fileName = i_fileName;
}

void SpriteRenderer::Start()
{
	gDrawables->push_back(std::make_unique<Sheet>(
		*pGfx,
		fileName,
		gameObject->position->x,
		gameObject->position->y,
		1.0f, 1.0f,
		0.0f));

	//Store reference to last element for modifications
	sheet = dynamic_cast<Sheet*>((gDrawables->back()).get());
}

void SpriteRenderer::Update()
{
	//Change parameters in sheet according to transform
	sheet->SetPosition(gameObject->position->x, gameObject->position->y);
}
