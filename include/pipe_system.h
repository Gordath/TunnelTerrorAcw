#ifndef PIPE_SYSTEM_H_
#define PIPE_SYSTEM_H_
#include "System.h"

class PipeSystem : public System {
public:

	void Process(std::vector<GameObject*>& list, double deltaTime) override;
};

#endif //PIPE_SYSTEM_H_