#include "PipeItem.h"
#include <GL/GLM/GTC/matrix_transform.inl>
#include "RenderComponent.h"

PipeItem::PipeItem(Mesh* m) : GameObject("pipeItem")
{
	RenderComponent* rc{ new RenderComponent(this) };
	rc->SetMesh(m);
	rc->SetMaterial(Material{ glm::vec4{ 1.0f, 1.0f, 0.0f, 0.1f }, glm::vec4{ 1.0f, 1.0f, 1.0f, 60.0f } });

//	_rotater = new GameObject{"rotater"};
//	RenderComponent *f = new RenderComponent{ _rotater };
////	f->SetMesh(m);
////	f->SetMaterial(Material{ glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f }, glm::vec4{ 1.0f, 1.0f, 1.0f, 60.0f } });
//	SetParent(_rotater);
}

void PipeItem::Position(const PipeDesc& pipeDesc, float curveRotation, float ringRotation)
{
	glm::mat4 mat;
//	_rotater->SetPosition(glm::vec3{ 0.0f, pipeDesc.curveRadius, 0.0f });
////	mat = glm::translate(mat, glm::vec3{ 0.0f, pipeDesc.pipeRadius, 0.0f });
//	mat = glm::rotate(mat, ringRotation, glm::vec3{ 1.0f, 0.0f, 0.0f });
//	_rotater->SetExtraXForm(mat);
//
//	static float f;
//	glm::mat4 xform;
//	xform = glm::rotate(xform, curveRotation, glm::vec3{ 0.0f, 0.0f, 1.0f });
//	xform = glm::translate(xform, glm::vec3{ 0.0f, pipeDesc.pipeRadius, 0.0f });
//	
//	xform = glm::scale(xform, glm::vec3{ 0.3f, 0.2f, 0.3f });
//
//	f += glm::radians(20.0f);
//
//	_extraXform = xform;
}

void PipeItem::Start()
{
}

void PipeItem::Update(double deltaTime)
{
}

void PipeItem::OnMessage(Message* msg)
{
	GameObject::OnMessage(msg);
}

void PipeItem::End()
{
}

void PipeItem::Reset()
{
}
