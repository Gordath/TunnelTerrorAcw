#ifndef PIPE_ITEM_GENERATOR_H_
#define PIPE_ITEM_GENERATOR_H_
#include <tuple>
#include <vector>
#include "PipeItem.h"
#include "GameObject.h"
#include "PipeDescription.h"

using PipeTuple = std::tuple< GameObject*, float, std::vector<PipeItem*> >;

class PipeItemGenerator {
public:
	virtual ~PipeItemGenerator() = default;

	virtual void Generate(PipeTuple& pipeTuple, const PipeDesc& pipeDesc) = 0;
};

#endif //PIPE_ITEM_GENERATOR_H_
