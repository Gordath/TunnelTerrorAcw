#pragma once

// GLM

#include "GL\GLM\GTC\type_ptr.hpp"

// Forward declarations
class Game;
class RenderComponent;
class Mesh;

// Platform independent renderer base class
// Basically represents a graphics context and its active shaders
class Renderer {
	// Data
public:
	glm::vec4 _clearColour; // Screen clear colour

	Renderer();
	virtual ~Renderer();

	glm::vec4 GetClearColour() const { return _clearColour; }
	void SetClearColour(glm::vec4 c) { _clearColour = c; }

	virtual void ClearScreen() = 0;

	virtual void Draw(const Mesh* mesh, glm::mat4 MVM, const glm::vec4& colour) = 0;
	virtual void Draw(RenderComponent* gob, glm::mat4 MVM);

	virtual void Destroy() = 0;

	virtual void Initialise(int width, int height) = 0;

	virtual void SwapBuffers() = 0;
};
