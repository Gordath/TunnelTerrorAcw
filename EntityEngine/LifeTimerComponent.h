#pragma once
#include "GameObjectComponent.h"

class LifeTimerComponent
		: public GameObjectComponent {
	// Data
protected:
	double _startingLifeTime; // Default starting lifetime (s)
	double _timeLeft; // Lifespan left (s)


	// Structors
public:
	LifeTimerComponent(GameObject* gob, double lifeTime);
	virtual ~LifeTimerComponent();

	double GetStartingLifeTime() const { return _startingLifeTime; }
	void SetStartingLifeTime(double v) { _startingLifeTime = v; }

	double GetLifeTimeLeft() const { return _timeLeft; }
	void SetLifeTimeLeft(double v) { _timeLeft = v; }
	void DecreaseLifeTime(double v) { _timeLeft -= v; }
	void ResetLifeTime() { _timeLeft = _startingLifeTime; }

	double GetPercentLifeLeft() const { return _startingLifeTime > 0 ? _timeLeft / _startingLifeTime : 0; }

	// Setup function -- called when parent object is initialised (using its own Start method)
	void Start() noexcept override;

	// Main update function (called every frame)
	void Update(double deltaTime) noexcept override;

	// Message handler (called when message occurs)
	void OnMessage(Message* msg) noexcept override;

	// Shutdown function -- called when parent object is destroyed
	void End() noexcept override;
};
