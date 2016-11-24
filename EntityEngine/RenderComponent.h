#pragma once
#include "GameObjectComponent.h"
#include "Mesh.h"
#include "Colour.h"
#include "GameObject.h"

class RenderComponent
	: public GameObjectComponent
{
	// Data
protected:
	Mesh*			_mesh;			// Vertex info
	Colour			_colour;		// Colour of object
	bool			_shouldDraw;	// Whether or not to draw

	// RenderComponent
public:
	RenderComponent(GameObject* gob);
	virtual ~RenderComponent();

	Mesh* GetMesh()							const	{ return _mesh; }
	void SetMesh(Mesh* m)							{ _mesh = m; }

	Colour GetColour()						const	{ return _colour; }
	void SetColour(Colour c)						{ _colour = c; }

	bool ShouldDraw()						const	{ return _shouldDraw; }
	void ShouldDraw(bool v)							{ _shouldDraw = v; }

	// Get position/scale/angle etc from parent object
	Vector4 GetPosition()					const { return _parent->GetPosition(); }
	float GetAngleX()						const	{ return _parent->GetAngleX(); }
	float GetAngleY()						const { return _parent->GetAngleY(); }
	float GetAngleZ()						const { return _parent->GetAngleZ(); }
	float GetScale()						const	{ return _parent->GetScale(); }
	
	Vector4 GetLocalPosition()					const { return _parent->GetLocalPosition(); }
	float GetLocalAngleX()						const { return _parent->GetLocalAngleX(); }
	float GetLocalAngleY()						const { return _parent->GetLocalAngleY(); }
	float GetLocalAngleZ()						const { return _parent->GetLocalAngleZ(); }
	float GetLocalScale()						const { return _parent->GetLocalScale(); }

	glm::mat4 GetExtraXform() const { return _parent->GetExtraXform(); }

	glm::mat4 GetXform() const { return _parent->GetXform(); }
	void CalcXform() const { _parent->CalcXform(); }

	// Setup function -- called when parent object is initialised (using its own Start method)
	void Start() override;

	// Main update function (called every frame)
	void Update(double deltaTime) override;

	// Message handler (called when message occurs)
	void OnMessage(Message* msg) override;

	// Shutdown function -- called when parent object is destroyed
	void End() override;

};