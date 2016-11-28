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

	Vertex(const glm::vec3& position,
	       const glm::vec3& normal,
	       const glm::vec3& tangent,
	       const glm::vec2& texcoord,
	       const glm::vec4& colour) : position(position),
	                                  normal(normal),
	                                  tangent(tangent),
	                                  texcoord(texcoord),
	                                  colour(colour)
	{
	}
};
