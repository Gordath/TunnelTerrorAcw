#include "tunnel_terror_game.h"
#include "Mesh.h"
#include "game_scene.h"

void TunnelTerrorGame::Initialise(Window* window)
{
	Game::Initialise(window);

	_renderer->SetClearColour(Colour{ 0.3f, 0.3f, 0.3f, 1.0f });

	Mesh *triangle = new Mesh();
	triangle->AddVertex({ -1, 0, 0.0, 1.0, 0.0, 0.0, 1.0 });
	triangle->AddVertex({ 0, 1, 0.0, 0.0, 1.0, 0.0, 1.0 });
	triangle->AddVertex({ 1, 0, 0.0, 0.0, 0.0, 1.0, 1.0 });

	AddMesh("triangle", triangle);

	for (auto mesh : _meshes) {
		mesh.second->CreateVBO(_renderer);
	}

	_sceneManager.PushScene(new GameScene);
}

void TunnelTerrorGame::OnKeyboard(int key, bool down)
{
	Game::OnKeyboard(key, down);
}

void TunnelTerrorGame::Render()
{
	// Clear screen
	_renderer->ClearScreen();

	_sceneManager.Render(&_renderSystem);

	_renderer->SwapBuffers();
}

void TunnelTerrorGame::Run()
{
	Game::Run();
	_sceneManager.Update(_deltaTime);
	Render();
}

void TunnelTerrorGame::ListenToMessage(Message* msg)
{

}
