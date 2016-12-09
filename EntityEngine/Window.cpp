#include "Window.h"
#include "Game.h"

Window* Window::TheWindow{ nullptr };

/******************************************************************************************************************/

Window::Window(Game* game, int width, int height)
	: _game(game),
	  _renderer(nullptr),
	  _width(width),
	  _height(height)
{
	// Set static singleton
	TheWindow = this;
	game->SetWindow(static_cast<Window*>(this));
}

/******************************************************************************************************************/

Window::~Window()
{
}

/******************************************************************************************************************/
