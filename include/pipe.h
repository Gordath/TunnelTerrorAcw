#ifndef PIPE_H_
#define PIPE_H_
#include "GameObject.h"
#include "Mesh.h"

class Pipe : public GameObject {
private:
	float _curveRadius;
	float _pipeRadius;

	int _curveSegments;
	int _pipeSegments;

	float _curveDistance = 0.25f;

	float _relativeRotation;

	void CreateFirstRing(float u, Vertex* vertArr) const;
	void CreateRing(float u, int i, Vertex* vertArr) const;
	Mesh* GenerateMesh();

public:
	Pipe() = default;

	Pipe(float curveRadius, float pipeRadius, float curveSegments, float pipeSegments, Renderer* renderer);

	glm::vec3 GetPointOnTorus(float u, float v) const;

	void SetCurveRadius(float curveRadius) { _curveRadius = curveRadius; }

	void SetPipeRadius(float pipeRadius) { _pipeRadius = pipeRadius; }

	void SetCurveSegments(float curveSegments) { _curveSegments = curveSegments; }

	void SetPipeSegments(float pipeSegments) { _pipeSegments = pipeSegments; }

	void SetRelativeRotation(float relativeRotation) { _relativeRotation = relativeRotation; }

	float GetCurveRadius() const { return _curveRadius; }

	float GetPipeRadius() const { return _pipeRadius; }

	int GetCurveSegments() const { return _curveSegments; }

	int GetPipeSegments() const { return _pipeSegments; }

	float GetRelativeRotation() const { return _relativeRotation; }
};

#endif //PIPE_H_
