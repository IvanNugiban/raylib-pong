#include "aiplayer.h"
#include "ball.h"
#include "raymath.h"

void AiPlayer::move(double deltaTime)
{
    constexpr float threshold = 5.0f;

    if (m_ball->y() < m_posY + m_height / 2 - threshold) {
        goUp(deltaTime);
    }
    else if (m_ball->y() > m_posY + m_height / 2 + threshold) {
        goDown(deltaTime);
    }
}
