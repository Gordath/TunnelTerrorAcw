#include "RenderSystem.h"
#include "GameObject.h"
#include "RenderComponent.h"

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

RenderSystem::RenderSystem()
	: _renderer(nullptr)
{
}

/******************************************************************************************************************/

RenderSystem::~RenderSystem()
{
}

/******************************************************************************************************************/
// Functions
/******************************************************************************************************************/

void RenderSystem::Process(std::vector<GameObject*>& list, double deltaTime)
{
	if (_renderer == nullptr)
		return;

	for (GameObject* obj : list) {

		if (obj->IsAlive()) {

			if (RenderComponent* rc = static_cast<RenderComponent*>(obj->GetComponent("render"))) {
				_renderer->Draw(rc, _M, _V, _P);
			}

		}
	}
}

/******************************************************************************************************************/
