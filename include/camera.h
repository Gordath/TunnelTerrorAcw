#ifndef CAMERA_H_
#define CAMERA_H_
#include "GameObject.h"
#include "GL/GLM/mat4x4.hpp"

class Camera : public GameObject {
private:
	glm::mat4 _cameraMatrix;

public:
	void Translate();
};

#endif //CAMERA_H_
