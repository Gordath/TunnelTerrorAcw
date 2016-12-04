#ifndef RANDOM_PIPE_ITEM_GENERATOR_H_
#define RANDOM_PIPE_ITEM_GENERATOR_H_

#include "PipeItemGenerator.h"
#include "Scene.h"

class RandomPipeItemGenerator : public PipeItemGenerator {
private:
	std::vector<PipeItem*> _items;
	Scene* _scene{ nullptr };

public:
	RandomPipeItemGenerator(const std::vector<PipeItem*>& items, Scene* scene)
		: _items(items), _scene(scene)
	{		
	}

	void Generate(PipeTuple& pipeTuple, const PipeDesc& pipeDesc) override;
};

#endif //RANDOM_PIPE_ITEM_GENERATOR_H_
