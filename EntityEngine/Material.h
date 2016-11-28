#ifndef MATERIAL_H_
#define MATERIAL_H_
#include <GL/GLM/detail/type_vec4.hpp>

struct Material {
	glm::vec4 diffuse;
	glm::vec4 specular; //specular.w is the shininess value.

	Material() = default;

	Material(const glm::vec4& diffuse, const glm::vec4& specular) : diffuse(diffuse), specular(specular)
	{
	}
};

#endif //MATERIAL_H_
