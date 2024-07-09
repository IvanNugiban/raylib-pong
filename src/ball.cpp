#include "ball.h"
#include "raylib.h"
#include "raymath.h"
#include "constants.h"

Ball::Ball(float posX, float posY, float radius, float speed) : Entity{ posX, posY, speed }, m_radius{ radius } {
	// Adjust position according to radius	
	setPosition({ posX, posY });
};
void Ball::move(double deltaTime)
{
	m_posX += m_direction.x * m_speed * deltaTime;
	m_posY += m_direction.y * m_speed * deltaTime;
}

void Ball::draw()
{
	DrawCircle(m_posX, m_posY, m_radius, Constants::baseColor);
}

void Ball::setPosition(const Vector2& pos)
{
	// Adjust position according to radius
	player1Collided = player2Collided = false;
	m_posX =  pos.x - m_radius;
	m_posY =  pos.y - m_radius;
}

void Ball::setDirection(const Vector2& direction)
{
	m_direction = Vector2Normalize(direction);
}

void Ball::checkCollisions(const Rectangle& top, const Rectangle& bottom, const Rectangle& player1, const Rectangle& player2)
{
	// Check collisions with borders

	if (CheckCollisionCircleRec({ m_posX, m_posY }, m_radius, top) || CheckCollisionCircleRec({ m_posX, m_posY }, m_radius, bottom)) {
			m_direction = { m_direction.x, -m_direction.y };
	};

	// Check player 1 collision
	if (CheckCollisionCircleRec({ m_posX, m_posY }, m_radius, player1) && !player1Collided) {
		player1Collided = true;
		player2Collided = false;
		m_direction = { -m_direction.x, m_direction.y };
	};

	// Check player 2 collision
	if (CheckCollisionCircleRec({ m_posX, m_posY }, m_radius, player2) && !player2Collided) {
		player1Collided = false;
		player2Collided = true;
		m_direction = { -m_direction.x, m_direction.y };
	};
}


