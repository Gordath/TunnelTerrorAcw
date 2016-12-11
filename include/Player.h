#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Message.h"
#include "Material.h"

class Mesh;

enum class PlayerControls {
	KEYBOARD,
	MOUSE
};

class Player : public GameObject {
private:
	bool _timeWarpCharge{ true };
	bool _timeWarpRecharged{ false };
	bool _timeWarpWarning{ false };
	bool _timeWarpExpired{ true };
	double _timeWarpActivationTime{ 0.0 };

	float _warpValue{ 0.0f };

public:
	Player(Mesh* mesh, const Material& material, PlayerControls controls, const glm::vec3& localPosition);
	void Update(double deltaTime) override;

	void OnMessage(Message* msg) override;
};

#endif //PLAYER_H_