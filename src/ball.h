
#pragma once

#include <vector>
#include "entity.h"
#include "raylib.h"
#include "constants.h"

class Ball : public Entity {
public:

	Ball(float posX, float posY, float radius, float speed = Constants::baseBallSpeed);

	virtual void move(double deltaTime) override;
	virtual void draw() override;
	virtual void setPosition(const Vector2& pos) override;
	void setDirection(const Vector2& direction);
	void checkCollisions(const Rectangle& top, const Rectangle& bottom, const Rectangle& player1, const Rectangle& player2);
private:
	Vector2 m_direction{1, 0};
	float m_radius{Constants::baseBallSpeed};

	// These variables are needed to make sure that the ball touches the player only once and does not get stuck in the player.
	bool player1Collided{false};
	bool player2Collided{ false };
};