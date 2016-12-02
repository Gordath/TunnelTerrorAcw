#ifndef RANDOM_PIPE_ITEM_GENERATOR_H_
#define RANDOM_PIPE_ITEM_GENERATOR_H_

#include "PipeItemGenerator.h"

class RandomPipeItemGenerator : public PipeItemGenerator {
private:
	PipeItem* _item{ nullptr };

public:
	void Generate(PipeTuple pipeTuple, PipeDesc pipeDesc) override;
};

#endif //RANDOM_PIPE_ITEM_GENERATOR_H_
