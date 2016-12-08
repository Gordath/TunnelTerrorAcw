#ifndef MATERIAL_H_
#define MATERIAL_H_
#include <GL/GLM/detail/type_vec4.hpp>
#include "Texture.h"

struct Material {
	glm::vec4 diffuse;
	glm::vec4 specular; //specular.w is the shininess value.

	Texture* textures[NUM_TEXTURES]{ nullptr, nullptr, nullptr };

	Material() = default;

	Material(const glm::vec4& diffuse, const glm::vec4& specular, Texture* textures) : diffuse(diffuse), specular(specular), textures{ textures }
	{
	}
};

#endif //MATERIAL_H_
