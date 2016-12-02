#pragma once
#include <vector>

class GameObject;
class RenderSystem;
class SceneManager;
class Message;

/// Represents an abstract scene, i.e. mode of the game
/// For example, MainMenu, Gameplay, GameOver etc
class Scene {
protected:
	SceneManager* _sceneManager;
	std::vector<GameObject*> _gameObjects; // The list of game objects

	// Structors
public:
	Scene() = default;
	virtual ~Scene();

	// Game objects
	std::vector<GameObject*>& GetGameObjects() { return _gameObjects; }
	void AddGameObject(GameObject* obj) { _gameObjects.push_back(obj); }

	void SetSceneManager(SceneManager* s) { _sceneManager = s; }
	SceneManager* GetSceneManager() const { return _sceneManager; }

	virtual void Initialise() = 0;

	// Respond to input
	virtual void OnKeyboard(int key, bool down) = 0;

	// Respond to messages
	virtual void OnMessage(Message* msg);

	/// Update current scene
	virtual void Update(double deltaTime, long time);

	// Render current scene
	virtual void Render(RenderSystem* renderer) = 0;


};
