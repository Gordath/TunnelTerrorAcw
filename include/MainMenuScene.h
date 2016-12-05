#ifndef MAIN_MENU_SCENE_H_
#define MAIN_MENU_SCENE_H_
#include "Scene.h"
#include "PipeNetwork.h"
#include <memory>

class MainMenuScene : public Scene {
protected:
	std::unique_ptr<PipeNetwork> _pipeNetwork;

	glm::mat4 M;
	glm::mat4 V;
	glm::mat4 P;

public:
	void Initialise() override;

	void OnKeyboard(int key, bool down) override;

	void Update(double deltaTime, long time) override;

	void Render(RenderSystem* renderer) override;
};

#endif //MAIN_MENU_SCENE_H_
