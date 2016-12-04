#ifndef BSPHERE_H_
#define BSPHERE_H_
#include <GL/GLM/detail/type_vec3.hpp>

struct BSphere {
	glm::vec3 center;
	float radius;

	BSphere() = default;

	BSphere(const glm::vec3& center, float radius)
		: center(center), radius(radius)
	{
	}
};

#endif //BSPHERE_H_
