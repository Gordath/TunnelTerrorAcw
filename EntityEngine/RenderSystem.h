#pragma once
#include "System.h"
#include "Renderer.h"
#include <vector>

class RenderComponent;

class RenderSystem : public System {
	// Data
protected:
	Renderer* _renderer;
	glm::mat4 _MVM;

	// Structors
public:
	RenderSystem();
	virtual ~RenderSystem();

	Renderer* GetRenderer() const { return _renderer; }
	void SetRenderer(Renderer* r) { _renderer = r; }
	glm::mat4 GetMVM() const { return _MVM; }
	void SetMVM(glm::mat4 m) { _MVM = m; }

	void Process(std::vector<GameObject*>& list, double deltaTime) override;
};
