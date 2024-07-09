#pragma once
#include "constants.h"
#include "entity.h"
#include "raylib.h"

class Player : public Entity{
public:

	Player() = default;
	Player(float posX, float posY, float speed = Constants::baseSpeed);

	virtual void move(double deltaTime) override;
	virtual void draw() override;
	Rectangle getRec();
	virtual void setPosition(const Vector2& pos) override;

protected:

	void goUp(double deltaTime);
	void goDown(double deltaTime);

	float m_width{ Constants::baseWidth };
	float m_height{ Constants::baseHeight };
};