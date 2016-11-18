#include "pipe.h"

Vector4 Pipe::getPointOnTorus(float u, float v) const
{
	float r = _curveRadius + _pipeRadius * cos(v);
	return Vector4{ r * sin(u), r * cos(u), _pipeRadius * sin(v) };
}
