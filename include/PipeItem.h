#ifndef PIPE_ITEM_H_
#define PIPE_ITEM_H_
#include "GameObject.h"
#include "PipeDescription.h"

class Mesh;

class PipeItem : public GameObject {
private:
	GameObject* _rotater{ nullptr };

public:
	PipeItem(Mesh *m);
	void Position(const PipeDesc& pipeDesc, float curveRotation, float ringRotation);

	void Start() override;

	void Update(double deltaTime) override;

	void OnMessage(Message* msg) override;

	void End() override;

	void Reset() override;

	GameObject* GetRotaterObject() const noexcept { return _rotater; }
};

#endif //PIPE_ITEM_H_