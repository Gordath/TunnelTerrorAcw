#ifndef MAIN_MENU_SCENE_H_
#define MAIN_MENU_SCENE_H_
#include "Scene.h"
#include "PipeNetwork.h"
#include <memory>
#include "Material.h"
#include "AudioManager.h"

enum class MainMenuState {
	INITIAL_MENU,
	SP_CONTROLS_SELECTION,
	TP_CONTROLS_SELECTION
};

class MainMenuScene : public Scene {
protected:
	std::unique_ptr<PipeNetwork> _pipeNetwork;

	glm::mat4 M;
	glm::mat4 V;
	glm::mat4 P;

	MainMenuState _menuState{ MainMenuState::INITIAL_MENU };
	bool _controlsSelected{ false };

	Material player1Material;
	Material player2Material;

	void DrawGameTitle(Renderer* renderer) const noexcept;
	void DrawInitialMenuText(Renderer* renderer) const noexcept;
	void DrawSPControlsSelectionText(Renderer* renderer) const noexcept;
	void DrawTPControlsSelectionText(Renderer* renderer) const noexcept;

public:
	void Initialise() override;

	void OnKeyboard(int key, bool down) override;

	void Update(double deltaTime, long time) override;

	void Render(RenderSystem* renderer) override;
};

#endif //MAIN_MENU_SCENE_H_
