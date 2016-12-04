#include "TunnelTerrorGame.h"
#include "Mesh.h"
#include "GameScene.h"
#include <sstream>

void TunnelTerrorGame::Initialise(Window* window)
{
	Game::Initialise(window);

	_renderer->SetClearColour(glm::vec4{ 0.3f, 0.3f, 0.3f, 0.0f });

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

	// Setup digit/letter meshes
	_digits.LoadFromFile("DigitsMesh.txt");
	_letters.LoadFromFile("LettersMesh.txt");

	for (int i = 0; i < _digits.NumMeshes(); i++) {
		std::stringstream num;
		num << i;
		Mesh* m{ _digits.GetMesh(num.str()) };
		m->CreateBuffers(_renderer);
		AddMesh(num.str(), m);
	}

	char letter = 'A';
	for (int i = 0; i < _letters.NumMeshes(); i++) {
		std::stringstream num;
		num << letter++;
		Mesh* m{ _letters.GetMesh(num.str()) };
		m->CreateBuffers(_renderer);
		AddMesh(num.str(), m);
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
