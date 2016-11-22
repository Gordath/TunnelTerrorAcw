#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

// Represents an abstract shader
class Shader {
public:
	Shader(void);
	virtual ~Shader(void);

private: // Disable copying
	Shader(const Shader&) = delete;
	Shader operator=(const Shader&) = delete;
};
