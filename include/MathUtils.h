#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_
#include <GL/GLM/detail/type_vec3.hpp>

inline glm::vec3 GetPointOnTorus(float u, float v, float curveRadius, float pipeRadius) noexcept
{
	float r = curveRadius + pipeRadius * cos(v);
	return glm::vec3{ r * sin(u), r * cos(u), pipeRadius * sin(v) };
}

inline glm::vec3 GetPointOnCurve(const PipeDesc& pipeDesc, float u) noexcept
{
	return glm::vec3{ pipeDesc.curveRadius * sin(u), pipeDesc.curveRadius * cos(u), 0.0f };
}

#endif //MATH_UTILS_H_
