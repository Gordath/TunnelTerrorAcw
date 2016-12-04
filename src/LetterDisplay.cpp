#include "LetterDisplay.h"
#include "Game.h"
#include <sstream>
#include "MultiRenderComponent.h"

/******************************************************************************************************************/

LetterDisplay::LetterDisplay()
	: GameObject("letterDisplay")
{
	// Create components (they will add themselves)
	MultiRenderComponent* rc{ new MultiRenderComponent(this) };
	rc->SetMaterial(Material{ glm::vec4{ 0.5f, 0.5f, 1.0f, 1.0f }, glm::vec4{} });
	for (char i = 'A'; i <= 'Z'; i++) {
		std::stringstream num;
		num << i;
		Mesh* m = Game::TheGame->GetMesh(num.str());
		if (m) {
			rc->AddMesh(num.str(), m);
		}
	}
	rc->SelectCurrentMesh("A");
	rc->ShouldDraw(true);

	_letter = 'A';
}

/******************************************************************************************************************/

LetterDisplay::~LetterDisplay()
{
}

/******************************************************************************************************************/

void LetterDisplay::Update(double deltaTime)
{
	MultiRenderComponent* rc = static_cast<MultiRenderComponent*>(GetComponent("render"));
	std::stringstream num;
	num << _letter;
	rc->SelectCurrentMesh(num.str());
}

/******************************************************************************************************************/
