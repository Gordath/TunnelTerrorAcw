#include "WordDisplay.h"
#include "Renderer.h"
#include "Message.h"
#include "Game.h"
#include "MultiRenderComponent.h"

/******************************************************************************************************************/

WordDisplay::WordDisplay()
	: GameObject("wordDisplay")
{
	_colour = glm::vec4{1.0f, 1.0f, 0.0f, 1.0f};
}

/******************************************************************************************************************/

WordDisplay::~WordDisplay()
{
}

/******************************************************************************************************************/

void WordDisplay::Update(double deltaTime)
{
}

/******************************************************************************************************************/

void WordDisplay::OnMessage(Message* msg)
{
}

/******************************************************************************************************************/

void WordDisplay::Reset()
{
}

/******************************************************************************************************************/

void WordDisplay::Render(Renderer* r, glm::mat4 M, glm::mat4 V, glm::mat4 P)
{
	glm::vec3 pos = _position;
	for (int i = 0; i < _word.length(); i++) {
		char c = _word[i];

		MultiRenderComponent* mrc{ nullptr };
		if (_letterDisplay.SetCurrentLetter(c)) {
			_letterDisplay.Update(0);
			_letterDisplay.SetPosition(pos);
			mrc = static_cast<MultiRenderComponent*>(_letterDisplay.GetComponent("render"));
			mrc->SetMaterial(Material{ _colour, glm::vec4{} });
		}

		pos.x += 0.1f;

		if (mrc) {
			r->Draw(mrc, M, V, P);
		}
	}
}

/******************************************************************************************************************/
