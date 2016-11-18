#ifndef DEBUG_DUMMY_H_
#define DEBUG_DUMMY_H_

#include "GameObject.h"

class Mesh;

class DebugDummy : public GameObject {
public:
	DebugDummy(Mesh *mesh);
};

#endif //DEBUG_DUMMY_H_