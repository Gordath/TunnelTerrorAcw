#include "debug_dummy.h"
#include "RenderComponent.h"

DebugDummy::DebugDummy(Mesh* mesh) : GameObject("debugDummy")
{
	RenderComponent* rc = new RenderComponent(this);
	rc->SetMesh(mesh);
	rc->ShouldDraw(true);
}

