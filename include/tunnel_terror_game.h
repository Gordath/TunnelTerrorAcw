#ifndef TUNNEL_TERROR_GAME_H_
#define TUNNEL_TERROR_GAME_H_

#include "Game.h"

class TunnelTerrorGame : public Game {
public:
	void Initialise(Window* window) override;

	void OnKeyboard(int key, bool down) override;

	void Render() override;

	void Run() override;

	void ListenToMessage(Message* msg) override;
};

#endif //TUNNEL_TERROR_GAME_H_
