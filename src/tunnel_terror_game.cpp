#include "tunnel_terror_game.h"

void TunnelTerrorGame::Initialise(Window* window)
{
	Game::Initialise(window);

	_renderer->SetClearColour(Colour{ 0.3f, 0.3f, 0.3f, 1.0f });

}

void TunnelTerrorGame::OnKeyboard(int key, bool down)
{
	Game::OnKeyboard(key, down);
}

void TunnelTerrorGame::Render()
{
	// Clear screen
	_renderer->ClearScreen();

	_renderer->SwapBuffers();
}

void TunnelTerrorGame::Run()
{
	Game::Run();

	Render();
}

void TunnelTerrorGame::ListenToMessage(Message* msg)
{

}
