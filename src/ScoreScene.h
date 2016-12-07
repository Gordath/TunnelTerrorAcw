#ifndef SCORE_SCENE_H_
#define SCORE_SCENE_H_
#include "Scene.h"
#include <memory>
#include "PipeNetwork.h"

using HighScoreTuple = std::tuple<std::wstring, unsigned int>;

class ScoreScene : public Scene {
protected:
	std::unique_ptr<PipeNetwork> _pipeNetwork;

	unsigned int _score{ 0 };

	std::vector<HighScoreTuple> _singlePlayerHighScores;
	std::vector<HighScoreTuple> _twoPlayerHighScores;

	wchar_t _initials[3]{'_', '_', '_'};
	int _initialsIndex{ 0 };

	bool _initialsSaved{ false };

	glm::mat4 M;
	glm::mat4 V;
	glm::mat4 P;

	void DrawScoreAndInitialsText(RenderSystem* renderer) const;
	void DrawHighScoreTables(RenderSystem* renderer) const;

	bool LoadSinglePlayerScore();
	bool LoadTwoPlayerScore();

	bool PersistSinglePlayerScore();
	bool PersistTwoPlayerScore();

public:
	ScoreScene(unsigned int score) : _score(score)
	{
	}

	void Initialise() override;

	void OnKeyboard(int key, bool down) override;

	void Update(double deltaTime, long time) override;

	void Render(RenderSystem* renderer) override;
};

#endif //SCORE_SCENE_H_
