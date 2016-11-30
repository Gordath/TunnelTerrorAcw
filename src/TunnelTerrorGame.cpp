#include "TunnelTerrorGame.h"
#include "Mesh.h"
#include "GameScene.h"

void TunnelTerrorGame::Initialise(Window* window)
{
	Game::Initialise(window);

	_renderer->SetClearColour(glm::vec4{ 0.3f, 0.3f, 0.3f, 1.0f });

	Mesh* cube = new Mesh();

	//front
	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, -0.5f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5, 0.5f, -0.5f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, -0.5f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, -0.5f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	//right
	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, -0.5f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, -0.5f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);


	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, 0.5f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, 0.5f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	//left
	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, 0.5f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, 0.5f, 0.5f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, -0.5f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, 0.5f, -0.5f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	//back
	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, 0.5f },
			glm::vec3{ 0.0f, 0.0f, 1.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, 0.5f },
			glm::vec3{ 0.0f, 0.0f, 1.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, 0.5f },
			glm::vec3{ 0.0f, 0.0f, 1.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, 0.5f, 0.5f },
			glm::vec3{ 0.0f, 0.0f, 1.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	//top
	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, 0.5f, -0.5f },
			glm::vec3{ 0.0f, 1.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, 0.5f, 0.5f },
			glm::vec3{ 0.0f, 1.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, -0.5f },
			glm::vec3{ 0.0f, 1.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, 0.5f },
			glm::vec3{ 0.0f, 1.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	//bottom
	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, -0.5f },
			glm::vec3{ 0.0f, -1.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, 0.5f },
			glm::vec3{ 0.0f, -1.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, -0.5f },
			glm::vec3{ 0.0f, -1.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, 0.5f },
			glm::vec3{ 0.0f, -1.0f, 0.0f },
			glm::vec3{},
			glm::vec2{},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	AddMesh("cube", cube);

	for (auto mesh : _meshes) {
		mesh.second->GenerateIndices(VertexWinding::CLOCKWISE);
		mesh.second->CreateBuffers(_renderer);
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
	_sceneManager.Update(_deltaTime, _currentTime);
	Render();
}

void TunnelTerrorGame::ListenToMessage(Message* msg)
{
}
