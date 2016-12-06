#pragma once

// Forward declarations
class Game;
class Renderer;


// Generic window class
// Handles window setup and input
class Window {
	// Constants and statics
public:
	// Singleton (sort of)
	static Window* TheWindow;

	Game* _game;
	Renderer* _renderer;
	int _width, _height;
	int _cursorX, _cursorY;

	Window(Game* game, int width, int height);
	virtual ~Window();

	Game* GetGame() const { return _game; }
	Renderer* GetRenderer() const { return _renderer; }

	virtual void Initialise() = 0;
};
