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
	// Delete game objects
	for (size_t i = 0; i < _gameObjects.size(); i++) {
		if (_gameObjects[i]->ShouldBeDeleted()) {
			delete _gameObjects[i];
			_gameObjects.erase(_gameObjects.begin() + i);
			i--;
		}
	}
}

/******************************************************************************************************************/
