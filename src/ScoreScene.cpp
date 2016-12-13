#include "ScoreScene.h"
#include "SceneManager.h"
#include "Game.h"
#include "Window.h"
#include <GL/GLM/GTC/matrix_transform.inl>
#include <locale>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "TunnelTerrorGame.h"

// Private methods --------------------------------------------------------------------------------------------
void ScoreScene::DrawScoreAndInitialsText(RenderSystem* renderer) const
{
	int winWidth{ _sceneManager->GetGame()->GetWindow()->_width };
	int winHeight{ _sceneManager->GetGame()->GetWindow()->_height };

	int verticalOffset = winHeight / 10;
	int verticalPos = verticalOffset;

	renderer->GetRenderer()->DrawString(L"YOUR SCORE", 100, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset;
	renderer->GetRenderer()->DrawString(std::to_wstring(_score), 180, winWidth / 2, winHeight / 3, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += 5.0f * verticalOffset;
	renderer->GetRenderer()->DrawString(L"ENTER YOUR INITIALS", 40, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	verticalPos += verticalOffset;
	renderer->GetRenderer()->DrawString(std::wstring{ _initials[0] } + L" " + std::wstring{ _initials[1] } + L" " + std::wstring{ _initials[2] },
	                                    40, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);

	if (_initialsIndex == 3) {
		verticalPos += verticalOffset;
		renderer->GetRenderer()->DrawString(L"PRESS ENTER TO CONTINUE",
		                                    40, winWidth / 2, verticalPos, 0xff0000ff, TextAlignment::CENTER);
	}
}

void ScoreScene::DrawHighScoreTables(RenderSystem* renderer) const
{
	int winWidth{ _sceneManager->GetGame()->GetWindow()->_width };
	int winHeight{ _sceneManager->GetGame()->GetWindow()->_height };

	renderer->GetRenderer()->DrawString(L"HIGH SCORES", 80, winWidth / 2, 0, 0xff0000ff, TextAlignment::CENTER);
	renderer->GetRenderer()->DrawString(L"PRESS ENTER TO CONTINUE", 30, winWidth / 2, winHeight - winHeight / 10, 0xff0000ff, TextAlignment::CENTER);
	renderer->GetRenderer()->DrawString(L"SINGLE PLAYER", 40, winWidth / 4, winHeight / 6, 0xff0000ff, TextAlignment::CENTER);
	renderer->GetRenderer()->DrawString(L"TWO PLAYER", 40, winWidth - winWidth / 4, winHeight / 6, 0xff0000ff, TextAlignment::CENTER);

	int verticalPos = winHeight / 6;
	int verticalOffset = winHeight / 13;
	for (int i = 0; i < 10; i++) {
		auto str{ std::get<std::wstring>(_singlePlayerHighScores[i]) };
		auto score{ std::to_wstring(std::get<unsigned int>(_singlePlayerHighScores[i])) };
		
		verticalPos += verticalOffset;
		renderer->GetRenderer()->DrawString(str + L"   " + score, 30, winWidth / 4, verticalPos, 0xff0000ff, TextAlignment::CENTER);
	}

	verticalPos = winHeight / 6;
	verticalOffset = winHeight / 13;
	for (int i = 0; i < 10; i++) {
		auto str{ std::get<std::wstring>(_twoPlayerHighScores[i]) };
		auto score{ std::to_wstring(std::get<unsigned int>(_twoPlayerHighScores[i])) };

		verticalPos += verticalOffset;
		renderer->GetRenderer()->DrawString(str + L"   " + score, 30, winWidth - winWidth / 4, verticalPos, 0xff0000ff, TextAlignment::CENTER);
	}
}

bool ScoreScene::LoadSinglePlayerScore()
{
	std::wifstream ifstr{ "singleplayer.scores" };

	if (!ifstr.is_open()) {
		std::cerr << "Failed to open file! singleplayer.scores" << std::endl;
		return false;
	}

	std::wstring line;
	int counter = 0;
	while (std::getline(ifstr, line) && counter < 10) {

		unsigned int idx{ line.find_first_of(',') };

		std::wstring initials{ line.substr(0, idx) };

		std::wstringstream ss;
		ss << line.substr(++idx, line.length());
		unsigned int score;
		ss >> score;

		_singlePlayerHighScores[counter] = std::make_tuple(initials, score);
		++counter;
	}

	return true;
}

bool ScoreScene::LoadTwoPlayerScore()
{
	std::wifstream ifstr{ "twoplayer.scores" };

	if (!ifstr.is_open()) {
		std::cerr << "Failed to open file! twoplayer.scores" << std::endl;
		return false;
	}

	std::wstring line;
	int counter = 0;
	while (std::getline(ifstr, line) && counter < 10) {

		unsigned int idx{ line.find_first_of(',') };

		std::wstring initials{ line.substr(0, idx) };

		std::wstringstream ss;
		ss << line.substr(++idx, line.length());
		unsigned int score;
		ss >> score;

		_twoPlayerHighScores[counter] = std::make_tuple(initials, score);
		++counter;
	}

	return true;
}

bool ScoreScene::PersistSinglePlayerScore()
{
	std::wofstream ofstr{ "singleplayer.scores", std::ios::trunc };

	if (!ofstr.is_open()) {
		std::cerr << "Failed to open file!" << std::endl;
		return false;
	}

	std::wstring initials{ _initials[0], _initials[1], _initials[2] };

	_singlePlayerHighScores.push_back(std::make_tuple(initials, _score));

	std::sort(_singlePlayerHighScores.begin(), _singlePlayerHighScores.end(),
	          [](auto a, auto b) {
		          return std::get<unsigned int>(a) > std::get<unsigned int>(b);
	          });

	for(auto highScoreTuple : _singlePlayerHighScores) {
		ofstr << std::get<std::wstring>(highScoreTuple) + L"," + std::to_wstring(std::get<unsigned int>(highScoreTuple)) + L"\n";
	}

	ofstr.close();

	return true;
}

bool ScoreScene::PersistTwoPlayerScore()
{
	std::wofstream ofstr{ "twoplayer.scores", std::ios::trunc };

	if (!ofstr.is_open()) {
		std::cerr << "Failed to open file!" << std::endl;
		return false;
	}

	std::wstring initials{ _initials[0], _initials[1], _initials[2] };

	_twoPlayerHighScores.push_back(std::make_tuple(initials, _score));

	std::sort(_twoPlayerHighScores.begin(), _twoPlayerHighScores.end(),
		[](auto a, auto b) {
		return std::get<unsigned int>(a) > std::get<unsigned int>(b);
	});

	for (auto highScoreTuple : _twoPlayerHighScores) {
		ofstr << std::get<std::wstring>(highScoreTuple) + L"," + std::to_wstring(std::get<unsigned int>(highScoreTuple)) + L"\n";
	}

	ofstr.close();

	return true;
}

// -----------------------------------------------------------------------------------------------------------

void ScoreScene::Initialise()
{
	PipeItem* smallObstacleTemplate{ new PipeItem{ Game::_resourceManager.Get<Mesh>(MODELS_PATH + L"obstacle.fbx") } };

	PipeDesc pipeDesc{ 7.0f, 1.0f, 20, 20, 0.25f };
	_pipeNetwork = std::make_unique<PipeNetwork>(pipeDesc, 3, 0.0055f, this);
	_pipeNetwork->AddPipeItemTemplate(smallObstacleTemplate);
	_pipeNetwork->Initialize(_sceneManager->GetGame()->GetRenderer());

	_singlePlayerHighScores.resize(10);
	_twoPlayerHighScores.resize(10);

	//Load high scores from files
	LoadSinglePlayerScore();
	LoadTwoPlayerScore();

	Game::_audioManager.play_stream("mad_science_trimmed2.ogg", 0.4f, AUDIO_PLAYMODE_LOOP);
}

void ScoreScene::OnKeyboard(int key, bool down)
{
	switch (down) {
	case true:
		switch (key) {
		case 13: //enter
			Game::_audioManager.play_sample(TunnelTerrorGame::_uiAction, 1.0f, AUDIO_PLAYMODE_ONCE);
			if (!_initialsSaved) {
				if (_sceneManager->GetGame()->GetGameMode() == GameMode::SINGLE_PLAYER) {
					if (!PersistSinglePlayerScore()) {
						break;
					}
				}
				else {
					if (!PersistTwoPlayerScore()) {
						break;
					}
				}
				_initialsSaved = true;
			}
			else {
				std::vector<Scene*> popedScenes;
				while (_sceneManager->GetSceneCount() != 1) {
					popedScenes.push_back(_sceneManager->GetCurrentScene());
					_sceneManager->PopScene();
				}

				for (auto scene : popedScenes) {
					delete scene;
				}
				Game::_audioManager.stop_streams();
				Game::_audioManager.play_stream("hyper_sun.ogg", 0.4f, AUDIO_PLAYMODE_LOOP);
			}
			break;
		case 8: //backspace
			if (_initialsIndex) {
				--_initialsIndex;
				_initials[_initialsIndex] = '_';
				Game::_audioManager.play_sample(TunnelTerrorGame::_uiCancel, 1.0f, AUDIO_PLAYMODE_ONCE);
			}
			break;
		default:
			if (key >= 32 && key < 127 && _initialsIndex < 3) {
				Game::_audioManager.play_sample(TunnelTerrorGame::_uiAction, 1.0f, AUDIO_PLAYMODE_ONCE);
				_initials[_initialsIndex] = std::toupper(static_cast<wchar_t>(key), std::locale());
				++_initialsIndex;
			}
			break;
		}
	case false:
		switch (key) {
		default:
			break;
		}
	}
}

void ScoreScene::Update(double deltaTime, long time)
{
	Scene::Update(deltaTime, time);

	_pipeNetwork->Update(deltaTime, time, false);

	P = glm::mat4{ 1.0f };

	float winWidth{ static_cast<float>(_sceneManager->GetGame()->GetWindow()->_width) };
	float winHeight{ static_cast<float>(_sceneManager->GetGame()->GetWindow()->_height) };
	P *= glm::perspectiveLH(static_cast<float>(glm::radians(90.0f)), winWidth / winHeight, 0.1f, 1000.0f);

	V = glm::mat4{ 1.0f };
	V = glm::rotate(V, static_cast<float>(glm::radians(-15.0f)), glm::vec3{ 1, 0, 0 });
	V = glm::rotate(V, static_cast<float>(glm::radians(-90.0f)), glm::vec3{ 0, 1, 0 });
	V = glm::translate(V, glm::vec3{ 0.0f, 0.0f, sin(time / 1000.0f) * 0.25f });
	V = glm::rotate(V, glm::radians(time / 60.0f), glm::vec3{ 1.0f, 0.0f, 0.0f });
	V = glm::rotate(V, cos(time / 1000.0f) * glm::pi<float>() / 7.5f, glm::vec3{ 0.0f, 1.0f, 0.0f });
	V = glm::translate(V, glm::vec3{ 0.0f, -0.3, 0.0f });
}

void ScoreScene::Render(RenderSystem* renderer)
{
	renderer->SetModelMatrix(glm::mat4{ 1 });
	renderer->SetViewMatrix(V);
	renderer->SetProjectionMatrix(P);
	renderer->Process(_gameObjects, 0);

	if (!_initialsSaved) {
		DrawScoreAndInitialsText(renderer);
	}
	else {
		DrawHighScoreTables(renderer);
	}
}
