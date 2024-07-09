#include <algorithm>
#include <iostream>
#include "player.h"
#include "raylib.h"
#include "constants.h"


Player::Player(float posX, float posY, float speed) : Entity{ posX, posY, speed} {
	// Adjust posY according to the height of player
	setPosition({ posX, posY });
}


void Player::move(double deltaTime)
{
	// Do nothing / movement not defined
}

void Player::draw() {
	DrawRectangle(m_posX, m_posY, m_width, m_height, Constants::baseColor);
}

Rectangle Player::getRec()
{
	return { m_posX, m_posY, m_width, m_height };
}

void Player::setPosition(const Vector2& pos)
{
	m_posX = pos.x - m_width / 2;
	m_posY = pos.y - m_height / 2;
}

void Player::goUp(double deltaTime)
{
	m_posY = std::max(m_posY - m_speed * deltaTime, Constants::borderHeight);
}

void Player::goDown(double deltaTime)
{
	m_posY = std::min(m_posY + m_speed * deltaTime, static_cast<double>(Constants::screenHeight) - m_height - Constants::borderHeight);
}
