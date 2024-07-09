#include "controlledplayer.h"
#include "raylib.h"

void ControlledPlayer::move(double deltaTime) {

	if (IsKeyDown(m_keyUp)) {
		goUp(deltaTime);
	}

	if (IsKeyDown(m_keyDown)) {
		goDown(deltaTime);
	}
}