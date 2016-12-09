#include "Window.h"
#include <stdlib.h>
#include <time.h>

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
}

/******************************************************************************************************************/

Window::~Window()
{
}

/******************************************************************************************************************/
