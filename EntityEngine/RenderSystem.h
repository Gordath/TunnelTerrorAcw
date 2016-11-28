#pragma once
#include "System.h"
#include "Renderer.h"
#include <vector>

class RenderComponent;

class RenderSystem : public System {
	// Data
protected:
	Renderer* _renderer;
	glm::mat4 _M;
	glm::mat4 _V;
	glm::mat4 _P;

	// Structors
public:
	RenderSystem();
	virtual ~RenderSystem();

	Renderer* GetRenderer() const { return _renderer; }
	void SetRenderer(Renderer* r) { _renderer = r; }
	
	const glm::mat4& GetModelMatrix() const { return _M; }
	void SetModelMatrix(glm::mat4 m) { _M = m; }

	const glm::mat4& GetViewMatrix() const { return _V; }
	void SetViewMatrix(const glm::mat4& view) { _V = view; }

	const glm::mat4& GetProjectionMatrix() const { return _P; };
	void SetProjectionMatrix(const glm::mat4& proj) { _P = proj; }

	void Process(std::vector<GameObject*>& list, double deltaTime) override;
};
