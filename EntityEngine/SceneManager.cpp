#include "SceneManager.h"
#include "Scene.h"

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

static std::vector<GameObject*> emptyVec;

SceneManager::SceneManager(Game* game)
	: _game(game)
{
}

/******************************************************************************************************************/

SceneManager::~SceneManager()
{
	for (int i = 0; i < _scenes.size(); ++i) {
		auto scene{ _scenes.top() };
		delete scene;
		_scenes.pop();
	}
}

/******************************************************************************************************************/
// Functions
/******************************************************************************************************************/

void SceneManager::AddGameObject(GameObject* obj)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene) {
		currentScene->AddGameObject(obj);
	}
}

/******************************************************************************************************************/

std::vector<GameObject*>& SceneManager::GetGameObjects()
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene) {
		return currentScene->GetGameObjects();
	}
	
	return emptyVec;
}

/******************************************************************************************************************/

void SceneManager::OnKeyboard(int key, bool down)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene) {
		currentScene->OnKeyboard(key, down);
	}
}

/******************************************************************************************************************/

void SceneManager::OnMessage(Message* msg)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene) {
		currentScene->OnMessage(msg);
	}
}

/******************************************************************************************************************/

/// Update current scene
void SceneManager::Update(double deltaTime, long time)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene) {
		currentScene->Update(deltaTime, time);
	}
}

/******************************************************************************************************************/

/// Render current scene
void SceneManager::Render(RenderSystem* renderer)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene) {
		currentScene->Render(renderer);
	}
}

/******************************************************************************************************************/

void SceneManager::PopScene()
{
	_scenes.pop();
}


void SceneManager::PushScene(Scene* s)
{
	_scenes.push(s);
	s->SetSceneManager(this);
	s->Initialise();
}

/******************************************************************************************************************/
