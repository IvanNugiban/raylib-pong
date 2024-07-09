#pragma once

struct Vector2;

class Entity {
public:

	Entity() = default;
	Entity(float posX, float posY, float speed) : m_posX{ posX }, m_posY{ posY }, m_speed{ speed } {};

	virtual void move(double deltaTime) = 0;
	virtual void draw() = 0;
	virtual void setPosition(const Vector2& pos) = 0;

	float x() const { return m_posX; };
	float y() const { return m_posY; };
	float speed() const { return m_speed; };

	void setSpeed(float speed) { m_speed = speed;};

protected:

	float m_posX{};
	float m_posY{};
	float m_speed{};
};