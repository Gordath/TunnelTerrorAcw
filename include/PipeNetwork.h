#ifndef PIPE_NETWORK_H_
#define PIPE_NETWORK_H_

#include "Scene.h"
#include "Mesh.h"
#include <deque>
#include "PipeItemGenerator.h"

using PipeTuple = std::tuple< GameObject*, float, std::vector<PipeItem*> >;

class PipeNetwork {
private:
	std::deque<PipeTuple> _pipeTuples;
	PipeDesc _pipeDesc;
	Mesh* _pipeMesh{ nullptr };

	const int _maxPipes;

	float _speed{ 0.01f };
	float _distanceTraveled{ 0.0f };
	float _distanceToAngle{ 0.0f };
	float _pipeRotation{ 0.0f };
	float _networkRotation{ 0.0f };

	GameObject* _currentPipe{ nullptr };
	GameObject* _pipeNetworkController{ nullptr };
	Scene* _scene{ nullptr };

	std::vector<PipeItem*> _pipeItemTemplates;
	PipeItemGenerator* _pipeItemGenerator{ nullptr };

	void CreateFirstRing(float u, Vertex* vertArr) const;
	void CreateRing(float u, int i, Vertex* vertArr) const;

	void GenerateMesh(Renderer* renderer);
	void GeneratePipe();

public:
	PipeNetwork(const PipeDesc& pipeDesc,
	            const int maxPipes,
	            float speed,
	            Scene* scene);

	~PipeNetwork();

	bool Initialize(Renderer* renderer);
	void Update(double deltaTime, long time);

	void AddPipeItemTemplate(PipeItem* item) noexcept { _pipeItemTemplates.push_back(item); }
};

#endif //PIPE_NETWORK_H_
