#ifndef PIPE_DESCRIPTION_H_
#define PIPE_DESCRIPTION_H_

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

#endif //PIPE_DESCRIPTION_H_
