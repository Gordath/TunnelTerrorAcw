#pragma once
#include "GameObject.h"
#include "LetterDisplay.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

#include <cmath>

class Renderer;

class TextDisplay : public GameObject {

private:
	glm::vec4 _color; // Colour to use
	std::string _text; // Word to display
	LetterDisplay _letterDisplay; // The letter display

	// Structors
public:
	TextDisplay();
	~TextDisplay();


	const glm::vec4& GetColor() const { return _color; }
	void SetColor(const glm::vec4& c) { _color = c; }

	const std::string& GetText() const { return _text; }
	void SetText(const std::string& text) { _text = text; }

	void Update(double deltaTime) override;

	void OnMessage(Message* msg) override;

	void Reset() override;

	void Render(Renderer* r, glm::mat4 MVM); // This is cheating really but meh
};
