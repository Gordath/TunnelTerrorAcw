#include "Game.h"
#include "Window.h"
#include "GameObject.h"
#include "KeyPressMessage.h"
#include "MouseMotionMessage.h"
#include "MouseClickMessage.h"
#include <iostream>


Game* Game::TheGame = nullptr;
ResourceManager Game::_resourceManager;

/******************************************************************************************************************/

Game::Game()
	: _quitFlag(false),
	  _sceneManager(this)
{
	for (int i = 0; i < 256; i++) _keyStates[i] = false;
	_currentTime = clock();

	TheGame = this;
	_window = nullptr;
}

/******************************************************************************************************************/

Game::~Game()
{
	Cleanup();
}

/******************************************************************************************************************/

void Game::Initialise(Window* w)
{
	_window = w;
	_renderer = w->GetRenderer();

	_renderSystem.SetRenderer(_renderer);
}

/******************************************************************************************************************/

void Game::OnKeyboard(int key, bool down)
{
	_keyStates[key] = down;

	// Create keypress message and send it to all objects
	KeyPressMessage msg(key, down);

	BroadcastMessage(&msg);

	_sceneManager.OnKeyboard(key, down);
}

/******************************************************************************************************************/

void Game::OnMouseMove(int x, int y)
{
	MouseMotionMessage msg{ glm::ivec2{x, y} };
	BroadcastMessage(&msg);
}

void Game::OnMouseClick(MouseButtonType button, int x, int y, bool pressed)
{
	MouseClickMessage msg{ button, glm::vec2{x, y}, pressed };
	BroadcastMessage(&msg);
}

void Game::OnResize(int width, int height)
{
	_window->_width = width;
	_window->_height = height;


	if(_renderer) {
		_renderer->Resize(width, height);
	}
}

void Game::Run()
{
	// Get delta time
	double temp_time = clock();
	_deltaTime = (temp_time - _currentTime) / CLOCKS_PER_SEC;
	_currentTime = temp_time;
}

/******************************************************************************************************************/

void Game::BroadcastMessage(Message* msg)
{
	ListenToMessage(msg);

	_sceneManager.OnMessage(msg);
}

/******************************************************************************************************************/
void Game::Cleanup()
{
	for (MeshMapIterator i = _meshes.begin();
		i != _meshes.end();
		++i) {
		delete i->second;
	}
	_meshes.clear();
}
