#include "pipe_network.h"
#include <GL/GLM/glm.hpp>
#include <GL/GLM/gtc/constants.inl>
#include <iostream>
#include <algorithm>
#include "RenderComponent.h"
#include <ctime>
#include <GL/GLM/GTC/matrix_transform.inl>


// Private methods ---------------------------------------------------------------------------------------------------------------------
void PipeNetwork::CreateFirstRing(float u, Vertex* vertArr) const
{
	float vStep = (2.0f * glm::pi<float>()) / _pipeDesc.pipeSegments;

	glm::vec3 posA{ GetPointOnTorus(0.0f, 0.0f, _pipeDesc.curveRadius, _pipeDesc.pipeRadius) };

	glm::vec3 ringCenterA{ GetPointOnCurve(0.0f) };
	glm::vec3 normalA{ glm::normalize(ringCenterA - posA) };
	glm::vec3 tangentA{ glm::normalize(GetPointOnTorus(0.001f, 0.0f, _pipeDesc.curveRadius, _pipeDesc.pipeRadius) - posA) };

	glm::vec3 posB{ GetPointOnTorus(u, 0.0f, _pipeDesc.curveRadius, _pipeDesc.pipeRadius) };
	glm::vec3 ringCenterB{ GetPointOnCurve(u) };
	glm::vec3 normalB{ glm::normalize(ringCenterB - posB) };
	glm::vec3 tangentB{ glm::normalize(GetPointOnTorus(u + 0.001f, 0.0f, _pipeDesc.curveRadius, _pipeDesc.pipeRadius) - posB) };

	Vertex vertexA{ posA, normalA, tangentA, glm::vec2{}, glm::vec4{ fabs(sin(u)), fabs(cos(u)), 1.0f, 1.0f } };
	Vertex vertexB{ posB, normalB, tangentB, glm::vec2{}, glm::vec4{ fabs(sin(u)), fabs(cos(u)), 1.0f, 1.0f } };

	for (int v = 1, i = 0; v <= _pipeDesc.pipeSegments; v++ , i += 4) {
		vertArr[i] = vertexA;

		glm::vec3 tmpPos{ GetPointOnTorus(0.0f, v * vStep, _pipeDesc.curveRadius, _pipeDesc.pipeRadius) };
		glm::vec3 normal{ glm::normalize(ringCenterA - tmpPos) };
		glm::vec3 tangent{ glm::normalize(GetPointOnTorus(0.001, v * vStep, _pipeDesc.curveRadius, _pipeDesc.pipeRadius) - tmpPos) };
		Vertex tmpVert{ tmpPos, normal, tangent, glm::vec2{}, glm::vec4{ 1.0f, fabs(cos(u)), 1.0f, 1.0f } };

		vertArr[i + 1] = vertexA = tmpVert;
		vertArr[i + 2] = vertexB;

		posA = GetPointOnTorus(u, v * vStep, _pipeDesc.curveRadius, _pipeDesc.pipeRadius);
		normal = glm::normalize(ringCenterB - posA);
		tmpVert = Vertex{ posA, normal, glm::vec3{}, glm::vec2{}, glm::vec4{ 1.0f, fabs(cos(u)), 1.0f, 1.0f } };

		vertArr[i + 3] = vertexB = tmpVert;
	}
}

void PipeNetwork::CreateRing(float u, int i, Vertex* vertArr) const
{
	float vStep = (2.0f * glm::pi<float>()) / _pipeDesc.pipeSegments;
	int ringOffset = _pipeDesc.pipeSegments * 4;

	glm::vec3 pos = GetPointOnTorus(u, 0.0f, _pipeDesc.curveRadius, _pipeDesc.pipeRadius);
	glm::vec3 ringCenter{ GetPointOnCurve(u) };
	glm::vec3 tangent{ GetPointOnTorus(u + 0.001f, 0.0f, _pipeDesc.curveRadius, _pipeDesc.pipeRadius) - pos };
	Vertex vertex{ pos, glm::normalize(ringCenter - pos), tangent, glm::vec2{}, glm::vec4{ 1.0f, 1.0f - u, 1.0f, 1.0f } };
	for (int v = 1; v <= _pipeDesc.pipeSegments; v++ , i += 4) {
		vertArr[i] = vertArr[i - ringOffset + 2];
		vertArr[i + 1] = vertArr[i - ringOffset + 3];
		vertArr[i + 2] = vertex;

		pos = GetPointOnTorus(u, v * vStep, _pipeDesc.curveRadius, _pipeDesc.pipeRadius);
		tangent = glm::normalize(GetPointOnTorus(u + 0.001f, v * vStep, _pipeDesc.curveRadius, _pipeDesc.pipeRadius) - pos);

		vertArr[i + 3] = vertex = Vertex{ pos, glm::normalize(ringCenter - pos), tangent, glm::vec2{}, glm::vec4{ 1.0f, 1.0f - u, 1.0f, 1.0f } };
	}
}

glm::vec3 PipeNetwork::GetPointOnTorus(float u, float v, float curveRadius, float pipeRadius)
{
	float r = curveRadius + pipeRadius * cos(v);
	return glm::vec3{ r * sin(u), r * cos(u), pipeRadius * sin(v) };
}

glm::vec3 PipeNetwork::GetPointOnCurve(float u) const
{
	return glm::vec3{ _pipeDesc.curveRadius * sin(u), _pipeDesc.curveRadius * cos(u), 0.0f };
}

void PipeNetwork::GenerateMesh(Renderer* renderer)
{
	int vertCount = _pipeDesc.pipeSegments * _pipeDesc.curveSegments * 4;
	Vertex* vertices = new Vertex[vertCount];

	float uStep = (2.0f * glm::pi<float>()) / _pipeDesc.curveSegments * _pipeDesc.curveDistance;
	//	_eulerAngles.z = -uStep * _pipeDesc.curveSegments;
	CreateFirstRing(uStep, vertices);

	int iDelta = _pipeDesc.pipeSegments * 4;
	for (int u = 2, i = iDelta; u <= _pipeDesc.curveSegments; u++ , i += iDelta) {
		CreateRing(u * uStep, i, vertices);
	}

	_pipeMesh = new Mesh;
	_pipeMesh->SetVertexData(vertices, vertCount);
	_pipeMesh->GenerateIndices(VertexWinding::ANTICLOCKWISE);
	_pipeMesh->CreateBuffers(renderer);

	delete[] vertices;
}

void PipeNetwork::GeneratePipe()
{
	//TODO.	
	float uStep = (2.0f * glm::pi<float>()) / _pipeDesc.curveSegments * _pipeDesc.curveDistance;
	//	_eulerAngles.z = -uStep * _pipeDesc.curveSegments;
}

// -------------------------------------------------------------------------------------------------------------------------------------

PipeNetwork::PipeNetwork(const PipeDesc& pipeDesc,
                         const int maxPipes,
                         float speed,
                         Scene* scene) : _pipeDesc(pipeDesc),
                                               _maxPipes(maxPipes),
                                               _speed(speed),
                                               _scene(scene)
{
	
}

PipeNetwork::~PipeNetwork()
{
	delete _pipeMesh;
}

bool PipeNetwork::Initialize(Renderer* renderer)
{
	//Seed the rand.
	srand(time(nullptr));

	//Resize the pipe tuple vector.
	_pipesAndRotations.resize(_maxPipes);

	//Generate the one and only pipe mesh.
	GenerateMesh(renderer);

	//Allocate the root node of the pipe network and add it to the scene.
	_pipeNetworkController = new GameObject("PipeNetworkCotroller");
	new RenderComponent(_pipeNetworkController);
	_scene->AddGameObject(_pipeNetworkController);

	//Calculate the distance to angle constant.
	_distanceToAngle = 360.0f / 2.0f * glm::pi<float>() * _pipeDesc.curveRadius;

	//Create the pipe tupples based on the PipeDesc structure.
	for (int i = 0; i < _maxPipes; i++) {
		_pipesAndRotations[i] = std::make_tuple(new GameObject("Pipe"), 0);// new Pipe(7, 1, 20, 20, _sceneManager->GetGame()->GetRenderer());
		GameObject* pipe{ std::get<GameObject*>(_pipesAndRotations[i]) };
		
		//Create a new RenderComponent for the GameObject and assign the mesh to it.
		RenderComponent* rc{ new RenderComponent(pipe) };
		rc->SetMesh(_pipeMesh);

		if (i == 0) {
			//The 1st pipe should have the root node of the network as a parent.
			pipe->SetParent(_pipeNetworkController);
			pipe->SetEulerAngles(glm::vec3{ pipe->GetEulerAngles().xy, 0 });
		}
		else {
			//Create the pipe hierarchy.
			GameObject* parent{ std::get<GameObject*>(_pipesAndRotations[i - 1]) };
			pipe->SetParent(parent);

			float uStep = (2.0f * glm::pi<float>()) / _pipeDesc.curveSegments * _pipeDesc.curveDistance;
			pipe->SetEulerAngles(glm::vec3{ pipe->GetEulerAngles().xy, -uStep * _pipeDesc.curveSegments });

			//Calculate a random relative rotation.
			std::get<float>(_pipesAndRotations[i]) = glm::radians((rand() % _pipeDesc.curveSegments) * (360.0f / _pipeDesc.pipeSegments));

			pipe->SetPosition(glm::vec3{});

			glm::mat4 extraXForm = glm::mat4(1);
			extraXForm = glm::translate(extraXForm, glm::vec3{ 0.0f, _pipeDesc.curveRadius, 0.0f });
			extraXForm = glm::rotate(extraXForm, std::get<float>(_pipesAndRotations[i]), glm::vec3{ 1.0f, 0.0f, 0.0f });
			extraXForm = glm::translate(extraXForm, glm::vec3{ 0.0f, -_pipeDesc.curveRadius, 0.0f });

			pipe->SetExtraXForm(extraXForm);
		}

		//Add the GameObject part of the tuple to the scene for rendering.
		_scene->AddGameObject(pipe);
	}

	//Align the first pipe with the origin.
	_currentPipe = std::get<GameObject*>(_pipesAndRotations[0]);
	_currentPipe->SetPosition(glm::vec3{ 0.0f, -_pipeDesc.curveRadius, 0.0f });

	return true;
}

void PipeNetwork::Update(double deltaTime)
{
	float delta{ _speed * static_cast<float>(deltaTime) };
	_distanceTraveled += delta;

	_pipeRotation += delta * _distanceToAngle;
	std::cout << _pipeRotation << std::endl;

	if (_pipeRotation >= 90.0f) {
		delta = (_pipeRotation - 90.0f) / _distanceToAngle;

		//shift the pipes and update the current pipe
		std::tuple<GameObject*, float> temp = _pipesAndRotations[0];
		for (int i = 1; i < _maxPipes; i++) {
			_pipesAndRotations[i - 1] = _pipesAndRotations[i];
		}
		_pipesAndRotations[_maxPipes - 1] = temp;
		std::replace(_scene->GetGameObjects().begin(), _scene->GetGameObjects().end(), _currentPipe, std::get<GameObject*>(_pipesAndRotations[0]));
		_currentPipe = std::get<GameObject*>(_pipesAndRotations[0]);
		_currentPipe->SetPosition(glm::vec3{ 0.0f, -_pipeDesc.curveRadius, 0.0f });
		_currentPipe->SetEulerAngles(glm::vec3{});
		_currentPipe->SetExtraXForm(glm::mat4{ 1 });
		_currentPipe->SetParent(_pipeNetworkController);

		_pipeRotation = delta * _distanceToAngle;

		_networkRotation += glm::degrees(std::get<float>(_pipesAndRotations[0]));
		if (_networkRotation < 0.0f) {
			_networkRotation += 360.0f;
		}
		else if (_networkRotation >= 360.0f) {
			_networkRotation -= 360.0f;
		}
	}

	_currentPipe->SetEulerAngles(glm::vec3{ 0.0f, 0.0f, glm::radians(_pipeRotation) });
	_pipeNetworkController->SetEulerAngles(glm::vec3{ glm::radians(_networkRotation), 0.0f, 0.0f });
}
