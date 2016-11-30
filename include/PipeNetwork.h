#ifndef PIPE_NETWORK_H_
#define PIPE_NETWORK_H_

#include "Scene.h"
#include "Mesh.h"
#include "GameObject.h"
#include <deque>

struct PipeDesc {
	float curveRadius;
	float pipeRadius;

	int curveSegments;
	int pipeSegments;

	float curveDistance{ 0.25f };
	float curveAngle;

	PipeDesc() = default;

	PipeDesc(float curveRadius,
	         float pipeRadius,
	         int curveSegments,
	         int pipeSegments,
	         float curveDistance) : curveRadius(curveRadius),
	                                pipeRadius(pipeRadius),
	                                curveSegments(curveSegments),
	                                pipeSegments(pipeSegments),
	                                curveDistance(curveDistance),
	                                curveAngle(360.0f * curveDistance)
	{
	}
};

class PipeNetwork {
private:
	std::deque< std::tuple<GameObject*, float> > _pipesAndRotations;
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

	void CreateFirstRing(float u, Vertex* vertArr) const;
	void CreateRing(float u, int i, Vertex* vertArr) const;
	static glm::vec3 GetPointOnTorus(float u, float v, float curveRadius, float pipeRadius);
	glm::vec3 GetPointOnCurve(float u) const;

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
};

#endif //PIPE_NETWORK_H_
