#pragma once
#include "GameObject.h"
#include "DigitDisplay.h"

// GLM
#include "GL\GLM\GLM.hpp"

#include <cmath>

class ScoreDisplay
		: public GameObject {
	// Constants
public:
	static const int NUM_DIGITS = 3;

	// Data
private:
	int _score; // Current score
	float _scoreCountdown; // When we're counting down after death
	DigitDisplay* _digits[NUM_DIGITS]; // To display the score
	bool _countdownMode; // Are we counting down?

	// Structors
public:
	ScoreDisplay();
	~ScoreDisplay();

	// Gets/sets
public:
	int GetScore() const { return _score; }
	void SetScore(int v) { _score = v; }

	void SetPosition(const glm::vec3& v) override;

	bool InCountdownMode() const { return _countdownMode; }
	void SetCountdownMode(bool v) { _countdownMode = v; }

	// Functions
public:
	void Update(double deltaTime) override;
	void OnMessage(Message* msg) override;
	void Reset() override;

	void StartCountdown()
	{
		_countdownMode = true;
		_scoreCountdown = static_cast<float>(_score);
	}
};
