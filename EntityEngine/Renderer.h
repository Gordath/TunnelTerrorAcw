#pragma once

// GLM
#undef DrawText
#include "GL\GLM\GTC\type_ptr.hpp"
#include <string>

struct Material;
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

	virtual void Draw(const Mesh* mesh, glm::mat4 M, glm::mat4 V, glm::mat4 P, const Material& material) = 0;
	virtual void Draw(RenderComponent* gob, glm::mat4 M, glm::mat4 V, glm::mat4 P);

	virtual void DrawString(const std::wstring text, float size, float xPos, float yPos, unsigned int colorABGR) = 0;

	virtual void Destroy() = 0;

	virtual void Initialise(int width, int height) = 0;

	virtual void SwapBuffers() = 0;
};
