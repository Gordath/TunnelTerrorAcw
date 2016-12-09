#pragma once
#include "GameObjectComponent.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Material.h"

class RenderComponent
		: public GameObjectComponent {
	// Data
protected:
	Mesh* _mesh; // Vertex info
	Material _material;
	bool _shouldDraw = true; // Whether or not to draw

	// RenderComponent
public:
	RenderComponent(GameObject* gob);
	virtual ~RenderComponent();

	Mesh* GetMesh() const { return _mesh; }
	void SetMesh(Mesh* m) { _mesh = m; }

	const Material& GetMaterial() const { return _material; }
	void SetMaterial(const Material& material) { _material = material; }

	bool ShouldDraw() const { return _shouldDraw; }
	void ShouldDraw(bool v) { _shouldDraw = v; }

	// Get position/scale/angle etc from parent object
	const glm::vec3& GetPosition() const { return _parent->GetPosition(); }
	const glm::vec3& GetEulerAngles() const { return  _parent->GetEulerAngles(); }
	const glm::vec3& GetScale() const { return _parent->GetScale(); }

	glm::mat4 GetExtraXform() const { return _parent->GetExtraXform(); }

	glm::mat4 GetXform() const { return _parent->GetXform(); }
	void CalcXform() const { _parent->CalcXform(); }

	// Setup function -- called when parent object is initialised (using its own Start method)
	void Start() noexcept override;

	// Main update function (called every frame)
	void Update(double deltaTime) noexcept override;

	// Message handler (called when message occurs)
	void OnMessage(Message* msg) noexcept override;

	// Shutdown function -- called when parent object is destroyed
	void End() noexcept override;

};
