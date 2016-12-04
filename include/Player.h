#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Message.h"

class Mesh;

class Player : public GameObject {
public:
	Player(Mesh* mesh);
	void Update(double deltaTime) override;

	void OnMessage(Message* msg) override;
};

#endif //PLAYER_H_