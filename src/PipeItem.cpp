#include "PipeItem.h"
#include <GL/GLM/GTC/matrix_transform.inl>


void PipeItem::Position(float pipeRadius, float curveRotation, float ringRotation)
{
	glm::mat4 xform;
	xform = glm::rotate(xform, -curveRotation, glm::vec3{0.0f, 0.0f, 1.0f});
	xform = glm::translate(xform, glm::vec3{ 0.0f, pipeRadius, 0.0f });
	xform = glm::rotate(xform, ringRotation, glm::vec3{1.0f, 0.0f, 0.0f});

	_extraXform = xform;
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
