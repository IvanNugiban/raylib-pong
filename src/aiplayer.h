
#pragma once

#include "Player.h"

class Ball;

class AiPlayer : public Player {

public:
	AiPlayer(float posX, float posY, Ball* ball) : Player{ posX, posY }, m_ball{ ball } {};

	virtual void move(double deltaTime) override; 

private:
	Ball* m_ball{};
};