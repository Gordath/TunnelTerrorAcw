#pragma once
#include "GameObject.h"
#include "LetterDisplay.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

#include <cmath>

class Renderer;

class WordDisplay
		: public GameObject {
	// Constants
public:

	// Data
private:
	glm::vec4 _colour; // Colour to use
	std::string _word; // Word to display
	LetterDisplay _letterDisplay; // The letter display

	// Structors
public:
	WordDisplay();
	~WordDisplay();

	// Gets/sets
public:
	const glm::vec4& GetColour() const { return _colour; }
	void SetColour(const glm::vec4& c) { _colour = c; }

	std::string GetWord() const { return _word; }
	void SetWord(std::string w) { _word = w; }

	// Functions
public:
	virtual void Update(double deltaTime);
	virtual void OnMessage(Message* msg);
	virtual void Reset();

	void Render(Renderer* r, glm::mat4 M, glm::mat4 V, glm::mat4 P); // This is cheating really but meh
};
