#pragma once

#include "player.h"
#include "raylib.h"

class ControlledPlayer : public Player {
public:
	ControlledPlayer(float posX, float posY, int keyUp = KEY_W, int keyDown = KEY_S) : Player{ posX, posY }, m_keyUp{ keyUp }, m_keyDown{ keyDown } {
	}

	virtual void move(double deltaTime) override;

private:
	int m_keyUp{};
	int m_keyDown{};
};