#ifndef PIPE_H_
#define PIPE_H_
#include "GameObject.h"

class Pipe : public GameObject {
private:
	float _curveRadius;
	float _pipeRadius;

	float _curveSegments;
	float _pipeSegments;

	Vector4 getPointOnTorus(float u, float v) const;

public:
	Pipe() = default;

	Pipe(float curveRadius, float pipeRadius, float curveSegments, float pipeSegments) : GameObject("pipe"),
	                                                                                     _curveRadius(curveRadius),
	                                                                                     _pipeRadius(pipeRadius),
	                                                                                     _curveSegments(curveSegments),
	                                                                                     _pipeSegments(pipeSegments)
	{
	}

	void setCurveRadius(float curveRadius) { _curveRadius = curveRadius; }

	void setPipeRadius(float pipeRadius) { _pipeRadius = pipeRadius; }

	void setCurveSegmanets(float curveSegments) { _curveSegments = curveSegments;  }

	void setPipeSegments(float pipeSegments) { _pipeSegments = pipeSegments; }

	float getCurveRadius() const { return _curveRadius; }

	float getPipeRadius() const { return _pipeRadius; }

	float getCurveSegments() const { return _curveSegments; }

	float getPipeSegments() const { return _pipeSegments; }


};

#endif //PIPE_H_
