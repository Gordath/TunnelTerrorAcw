#pragma once
#include <stack>
#include <vector>

class RenderSystem;
class Scene;
class Game;
class GameObject;
class Message;

/// Handles the Scenes for a game
class SceneManager {
protected:
	Game* _game;
	std::stack<Scene*> _scenes;

public:
	SceneManager(Game* _game);
	~SceneManager();

	Scene* GetCurrentScene() const
	{
		if (_scenes.size() > 0) {
			return _scenes.top();
		}
		
		return nullptr;
	}

	size_t GetSceneCount() const noexcept { return _scenes.size(); }

	Game* GetGame() const { return _game; }

	// Game object handling
	void AddGameObject(GameObject* obj);

	std::vector<GameObject*>& GetGameObjects();

	/// Respond to input
	void OnKeyboard(int key, bool down);

	/// Respond to messages
	void OnMessage(Message* msg);

	/// Update current scene
	void Update(double deltaTime, long time = 0);

	/// Render current scene
	void Render(RenderSystem* renderer);

	/// Pop the top scene. If no scenes remain, we should quit.
	void PopScene();

	/// Push a new scene
	void PushScene(Scene* s);
};
