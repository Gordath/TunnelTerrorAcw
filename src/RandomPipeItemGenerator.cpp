#include "RandomPipeItemGenerator.h"
#include "RenderComponent.h"
#include <iostream>
#include "MathUtils.h"
#include <GL/GLM/gtc/constants.inl>
#include <GL/GLM/GTC/matrix_transform.inl>


void RandomPipeItemGenerator::Generate(PipeTuple& pipeTuple, const PipeDesc& pipeDesc)
{
	float uStep{ pipeDesc.curveAngle / pipeDesc.curveSegments };
	float angle = 0;

	for (int i = 0; i < pipeDesc.curveSegments; ++i) {
		float randV{ static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * glm::pi<float>() * 2.0f };

		glm::vec3 pos{ GetPointOnCurve(pipeDesc, glm::radians(angle)) };
		angle += uStep;

		PipeItem* randSelection{ _items[rand() % _items.size()] };
		RenderComponent* selectionRc{ static_cast<RenderComponent*>(randSelection->GetComponent("render")) };

		PipeItem* pipeItem{ new PipeItem(selectionRc->GetMesh()) };

		glm::mat4 xform;
		xform = glm::translate(xform, pos);
		xform = glm::rotate(xform, -glm::radians(angle), glm::vec3{ 0.0f, 0.0f, 1.0f });
		xform = glm::rotate(xform, randV, glm::vec3{ 1.0f, 0.0f, 0.0f });
		xform = glm::translate(xform, glm::vec3{ 0.0f, pipeDesc.pipeRadius - randSelection->GetScale().y / 2.0f, 0.0f });
		xform = glm::scale(xform, randSelection->GetScale());
		pipeItem->SetExtraXForm(xform);

		GameObject* parent{ std::get<GameObject*>(pipeTuple) };
		pipeItem->SetParent(parent);

		std::get<std::vector<PipeItem*>>(pipeTuple).push_back(pipeItem);

		_scene->AddGameObject(pipeItem);
	}

}
