#ifndef PIPE_H_
#define PIPE_H_
#include "GameObject.h"
#include "Mesh.h"

class Pipe : public GameObject {
private:
	float _curveRadius;
	float _pipeRadius;

	float _curveSegments;
	float _pipeSegments;

	void CreateFirstRing(float u, Vertex* vertArr) const;
	void CreateRing(float u, int i, Vertex* vertArr) const;
	Mesh* GenerateMesh() const;

public:
	Pipe() = default;

	Pipe(float curveRadius, float pipeRadius, float curveSegments, float pipeSegments, Renderer* renderer);

	Vector4 GetPointOnTorus(float u, float v) const;

	void SetCurveRadius(float curveRadius) { _curveRadius = curveRadius; }

	void SetPipeRadius(float pipeRadius) { _pipeRadius = pipeRadius; }

	void SetCurveSegments(float curveSegments) { _curveSegments = curveSegments; }

	void SetPipeSegments(float pipeSegments) { _pipeSegments = pipeSegments; }

	float SetCurveRadius() const { return _curveRadius; }

	float GetPipeRadius() const { return _pipeRadius; }

	float GetCurveSegments() const { return _curveSegments; }

	float GetPipeSegments() const { return _pipeSegments; }
};

#endif //PIPE_H_
