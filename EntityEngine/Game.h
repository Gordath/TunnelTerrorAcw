#pragma once
#include <time.h>
#include <map>
#include <vector>

// Systems
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "CollisionSystem.h"

#include "SceneManager.h"
#include "MouseClickMessage.h"
#include "ResourceManager.h"

// Forward declarations
class GameObject;
class Mesh;
class Message;
class Renderer;
class Window;

// Typedefs
typedef std::map<std::string, Mesh*> MeshMap;
typedef std::map<std::string, Mesh*>::iterator MeshMapIterator;

enum class GameMode {
	SINGLE_PLAYER,
	MULTI_PLAYER
};

// Generic game class
class Game {
protected:
	double _currentTime; // Current time for delta time purposes
	double _deltaTime; // Time since last frame
	bool _keyStates[256]; // Keyboard status
	bool _quitFlag; // Quit flag; when true, we quit
	Renderer* _renderer { nullptr }; // The renderer
	Window* _window; // The game window

	// Meshes
	MeshMap _meshes; // The map of meshes

	// Systems
	RenderSystem _renderSystem; // To handle rendering

	// Scene Manager
	SceneManager _sceneManager;

	GameMode _gameMode;

public:
	static Game* TheGame;
	static ResourceManager _resourceManager;

	Game();
	virtual ~Game();

	// Meshes
	Mesh* GetMesh(std::string name);
	void AddMesh(std::string name, Mesh* mesh) { _meshes[name] = mesh; }

	// Quit flag
	bool GetQuitFlag() const { return _quitFlag; }
	void SetQuitFlag(bool v) { _quitFlag = v; }

	void SetGameMode(GameMode gameMode) noexcept { _gameMode = gameMode; }
	GameMode GetGameMode() const noexcept { return _gameMode; }

	// Renderer
	Renderer* GetRenderer() const { return _renderer; }

	Window* GetWindow() const { return _window; }

	void AddGameObject(GameObject* obj) { _sceneManager.AddGameObject(obj); }
	std::vector<GameObject*>& GetGameObjects() { return _sceneManager.GetGameObjects(); }

	// Initialise game
	virtual void Initialise(Window* w);

	// Keyboard input
	virtual void OnKeyboard(int key, bool down);

	virtual void OnMouseMove(int x, int y);

	virtual void OnMouseClick(MouseButtonType button, int x, int y, bool pressed);

	virtual void OnResize(int width, int height);

	// Draw everything
	virtual void Render() = 0;

	// Main game loop (update)
	virtual void Run();

	// Message system
	void BroadcastMessage(Message* msg);

	// The game can respond to messages too
	virtual void ListenToMessage(Message* msg)
	{
	}

	void Cleanup();
};


inline Mesh* Game::GetMesh(std::string name)
{
	// Found
	MeshMapIterator i = _meshes.find(name);
	if (i != _meshes.end()) {
		return i->second;
	}
	// Not found
	return nullptr;
}
