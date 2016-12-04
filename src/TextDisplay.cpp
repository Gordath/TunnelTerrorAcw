#include "TextDisplay.h"
#include "Renderer.h"
#include "Message.h"
#include "Game.h"
#include "MultiRenderComponent.h"

/******************************************************************************************************************/

TextDisplay::TextDisplay()
	: GameObject("wordDisplay")
{
	_color = glm::vec4{ 1.0f, 1.0f, 0.0, 1.0f };
}

/******************************************************************************************************************/

TextDisplay::~TextDisplay()
{
}

/******************************************************************************************************************/

void TextDisplay::Update(double deltaTime)
{
}

/******************************************************************************************************************/

void TextDisplay::OnMessage(Message* msg)
{
}

/******************************************************************************************************************/

void TextDisplay::Reset()
{
}

/******************************************************************************************************************/

void TextDisplay::Render(Renderer* r, glm::mat4 MVM)
{
	glm::vec3 pos = _position;
	for (int i = 0; i < _text.length(); i++) {
		char c = _text[i];

		MultiRenderComponent* mrc{ nullptr };
		if (_letterDisplay.SetCurrentLetter(c)) {
			_letterDisplay.Update(0);
			_letterDisplay.SetPosition(pos);
			mrc = static_cast<MultiRenderComponent*>(_letterDisplay.GetComponent("render"));
			mrc->SetMaterial(Material{ _color, glm::vec4{} });
		}

		pos.x += 0.1f;

		if (mrc) {
			//TODO: Fix the drawing here.
			//r->Draw(mrc, MVM);
		}
	}
}

/******************************************************************************************************************/
