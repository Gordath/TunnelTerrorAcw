#include "RandomPipeItemGenerator.h"
#include "RenderComponent.h"
#include <GL/GLM/detail/func_trigonometric.inl>
#include <iostream>
#include "MathUtils.h"
#include <GL/GLM/gtc/constants.inl>


void RandomPipeItemGenerator::Generate(PipeTuple& pipeTuple, const PipeDesc& pipeDesc)
{
	float uStep{ pipeDesc.curveAngle / pipeDesc.curveSegments };
	float angle = 0;

	for (int i = 0; i < pipeDesc.curveSegments / 2 ; ++i) {
		float randU{ static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * glm::pi<float>() / 2.0f };
		float randV{ static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * glm::pi<float>() * 2.0f };

		glm::vec3 pos{ GetPointOnTorus(glm::radians(angle) , randV, pipeDesc.curveRadius, pipeDesc.pipeRadius) };
		angle += uStep;

		PipeItem* randSelection{ _items[0] };
		RenderComponent* selectionRc{ static_cast<RenderComponent*>(randSelection->GetComponent("render")) };

		PipeItem* pipeItem{ new PipeItem(selectionRc->GetMesh()) };

		pipeItem->SetPosition(pos);
		pipeItem->SetEulerAngles(glm::vec3{ 0.0f, 0.0f, -std::get<float>(pipeTuple) });
		pipeItem->SetScale(glm::vec3{ 0.3f, 2.3f, 0.3f });

		GameObject* parent{ std::get<GameObject*>(pipeTuple) };
		pipeItem->SetParent(parent);

		std::get<std::vector<PipeItem*>>(pipeTuple).push_back(pipeItem);

		_scene->AddGameObject(pipeItem);
	}

}
