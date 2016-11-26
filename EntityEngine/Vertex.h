#pragma once
#include <GL/GLM/detail/type_vec4.hpp>
#include <GL/GLM/detail/type_vec3.hpp>
#include <GL/GLM/detail/type_vec2.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec2 texcoord;
	glm::vec4 colour;

	Vertex() = default;
	Vertex(const glm::vec3& position, const glm::vec4& colour) : position(position), colour(colour) {}
};
