#include "TunnelTerrorGame.h"
#include "Mesh.h"
#include "GameScene.h"
#include <sstream>
#include "MainMenuScene.h"
#include "Texture_DX.h"

AudioSample* TunnelTerrorGame::_speedUp{ nullptr };
AudioSample* TunnelTerrorGame::_uiAction{ nullptr };
AudioSample* TunnelTerrorGame::_uiCancel{ nullptr };
AudioSample* TunnelTerrorGame::_timeWarpActivation{ nullptr };
AudioSample* TunnelTerrorGame::_timeWarpWarning{ nullptr };
AudioSample* TunnelTerrorGame::_timeWarpReady{ nullptr };

void TunnelTerrorGame::Initialise(Window* window)
{
	Game::Initialise(window);

	_speedUp = new AudioSample;
	_speedUp->load("data/audio/speed_up.ogg");

	_uiAction = new AudioSample;
	_uiAction->load("data/audio/ui_action.ogg");

	_uiCancel = new AudioSample;
	_uiCancel->load("data/audio/ui_cancel.ogg");

	_timeWarpActivation = new AudioSample;
	_timeWarpActivation->load("data/audio/time_warp_activation.ogg");
	
	_timeWarpWarning = new AudioSample;
	_timeWarpWarning->load("data/audio/time_warp_warning.ogg");

	_timeWarpReady = new AudioSample;
	_timeWarpReady->load("data/audio/time_warp_ready.ogg");

	_renderer->SetClearColour(glm::vec4{ 0.0f, 0.0f, 0.0f, 0.0f });

	Mesh* cube = new Mesh();

	//front
	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, -0.5f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec3{ 1.0f, 0.0f, 0.0f},
			glm::vec2{0, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5, 0.5f, -0.5f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec3{ 1.0f, 0.0f, 0.0f},
			glm::vec2{0, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, -0.5f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec3{ 1.0f, 0.0f, 0.0f},
			glm::vec2{1, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, -0.5f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec2{1, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	//right
	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, -0.5f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec3{ 0.0f, 0.0f, 1.0f },
			glm::vec2{0, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, -0.5f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec3{ 0.0f, 0.0f, 1.0f },
			glm::vec2{0, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);


	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, 0.5f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec3{0.0f, 0.0f, 1.0f},
			glm::vec2{1, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, 0.5f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec3{ 0.0f, 0.0f, 1.0f },
			glm::vec2{1, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	//left
	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, 0.5f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec2{0, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, 0.5f, 0.5f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec2{0, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, -0.5f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec2{1, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, 0.5f, -0.5f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec3{ 0.0f, 0.0f, -1.0f },
			glm::vec2{1, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	//back
	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, 0.5f },
			glm::vec3{ 0.0f, 0.0f, 1.0f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec2{0, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, 0.5f },
			glm::vec3{ 0.0f, 0.0f, 1.0f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec2{0, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, 0.5f },
			glm::vec3{ 0.0f, 0.0f, 1.0f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec2{1, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, 0.5f, 0.5f },
			glm::vec3{ 0.0f, 0.0f, 1.0f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec2{1, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	//top
	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, 0.5f, -0.5f },
			glm::vec3{ 0.0f, 1.0f, 0.0f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec2{0, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, 0.5f, 0.5f },
			glm::vec3{ 0.0f, 1.0f, 0.0f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec2{0, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, -0.5f },
			glm::vec3{ 0.0f, 1.0f, 0.0f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec2{1, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, 0.5f, 0.5f },
			glm::vec3{ 0.0f, 1.0f, 0.0f },
			glm::vec3{ 1.0f, 0.0f, 0.0f },
			glm::vec2{1, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	//bottom
	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, -0.5f },
			glm::vec3{ 0.0f, -1.0f, 0.0f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec2{0, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ 0.5f, -0.5f, 0.5f },
			glm::vec3{ 0.0f, -1.0f, 0.0f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec2{0, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, -0.5f },
			glm::vec3{ 0.0f, -1.0f, 0.0f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec2{1, 0},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	cube->AddVertex(
		Vertex{
			glm::vec3{ -0.5f, -0.5f, 0.5f },
			glm::vec3{ 0.0f, -1.0f, 0.0f },
			glm::vec3{ -1.0f, 0.0f, 0.0f },
			glm::vec2{1, 1},
			glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
		}
	);

	AddMesh("cube", cube);

	Mesh* m = _resourceManager.Get<Mesh>(MODELS_PATH + L"player11.fbx");
	m->CreateBuffers(_renderer);

	m = _resourceManager.Get<Mesh>(MODELS_PATH + L"obstacle.fbx");
	m->CreateBuffers(_renderer);

	for (auto mesh : _meshes) {
		mesh.second->GenerateIndices(VertexWinding::CLOCKWISE);
		mesh.second->CreateBuffers(_renderer);
	}

	_sceneManager.PushScene(new MainMenuScene);
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
	_sceneManager.OnMessage(msg);
}
