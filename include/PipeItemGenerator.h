#ifndef PIPE_ITEM_GENERATOR_H_
#define PIPE_ITEM_GENERATOR_H_
#include "PipeNetwork.h"

class PipeItemGenerator {
public:
	virtual ~PipeItemGenerator() = default;

	virtual void Generate(PipeTuple pipeTuple, PipeDesc pipeDesc) = 0;
};

#endif //PIPE_ITEM_GENERATOR_H_
