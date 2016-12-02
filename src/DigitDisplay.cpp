#include "DigitDisplay.h"
#include "Game.h"
#include <sstream>
#include "MultiRenderComponent.h"

/******************************************************************************************************************/

DigitDisplay::DigitDisplay()
	: GameObject("digitDisplay")
{
	// Create components (they will add themselves)
	MultiRenderComponent* rc = new MultiRenderComponent(this);
	rc->SetMaterial(Material{ glm::vec4{ 0.5f, 0.5f, 1.0f, 1.0f }, glm::vec4{} });
	for (int i = 0; i < 10; i++) {
		std::stringstream num;
		num << i;
		rc->AddMesh(num.str(), Game::TheGame->GetMesh(num.str()));
	}
	rc->SelectCurrentMesh("0");
	rc->ShouldDraw(true);

	_number = 0;
}

/******************************************************************************************************************/

DigitDisplay::~DigitDisplay()
{
}

/******************************************************************************************************************/

void DigitDisplay::Update(double deltaTime)
{
	MultiRenderComponent* rc = static_cast<MultiRenderComponent*>(GetComponent("render"));
	std::stringstream num;
	num << _number;
	rc->SelectCurrentMesh(num.str());
}

/******************************************************************************************************************/
