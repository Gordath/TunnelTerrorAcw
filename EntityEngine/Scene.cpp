#include "Scene.h"
#include "GameObject.h"

/******************************************************************************************************************/

Scene::~Scene()
{
	for (auto gameObject : _gameObjects) {
		delete gameObject;
	}
	_gameObjects.clear();
}

/******************************************************************************************************************/
// Functions
/******************************************************************************************************************/

void Scene::OnMessage(Message* msg)
{
	for (auto gameObject : _gameObjects) {
		if (gameObject->IsAlive()) {
			gameObject->OnMessage(msg);
		}
	}
}

/******************************************************************************************************************/

void Scene::Update(double deltaTime, long time)
{
	auto it{ _gameObjects.begin() };
	while(it != _gameObjects.end()) {
		//Delete else update.
		GameObject* gobj{ *it };
		if (gobj->ShouldBeDeleted()) {
			delete gobj;
			it = _gameObjects.erase(it);
		}
		else {
			gobj->Update(deltaTime);
			++it;
		}
	}
}

/******************************************************************************************************************/
