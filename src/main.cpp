#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "controlledplayer.h"
#include "constants.h"
#include "helpers.h"
#include "ball.h"
#include "aiplayer.h"


enum class GameState {
	beginScreen,
	counter,
	inProcess,
	gameOver
};

GameState gameState{ GameState::beginScreen };
Ball ball{ Constants::screenWidth / 2, Constants::screenHeight / 2, Constants::baseBallRadius };
ControlledPlayer player1{ Constants::padding, Constants::screenHeight / 2 };
Player* player2{};
Rectangle top{ 0, 0, Constants::screenWidth, Constants::borderHeight }, bottom{ 0, Constants::screenHeight - Constants::borderHeight, Constants::screenWidth, Constants::borderHeight };

bool gameRestarting{false};
bool player1Won{ false };

double counter{ 3.0 };
double restartTimer{ 1.0 };
int player1Score{};
int player2Score{};

void resetVariables() {
	ball.setSpeed(Constants::baseBallSpeed);
	ball.setPosition({ Constants::screenWidth / 2, Constants::screenHeight / 2 });
	player1.setPosition({ Constants::padding, Constants::screenHeight / 2 });
	player2->setPosition({ Constants::screenWidth - Constants::padding, Constants::screenHeight / 2 });
}

void resetGame() {

	resetVariables();

	// Reset scores
	player1Score = 0;
	player2Score = 0;

	// Get back to start screen

	restartTimer = 3.0;
	counter = 3.0;
	gameState = GameState::gameOver;
}

void startNewRound() {
	resetVariables();
	counter = 2.0;
	gameState = GameState::counter;
}

void checkWinConditions() {

	if (gameRestarting && restartTimer < 0) {
		// Restart game or start new round
		if (player1Score == 3 || player2Score == 3) {
			player1Won = player1Score == 3;
			resetGame();
		}

		else startNewRound();

		gameRestarting = false;
	}

	else if (gameRestarting) return;

	bool scored{ false };

	// Check if left player scored
	if (ball.x() > Constants::screenWidth) {
		player1Won = true;
		player1Score++;
		scored = true;
	}

	// Check if right player scored
	else if (ball.x() < 0) {
		player1Won = false;
		player2Score++;
		scored = true;
	}

	if (!scored) return;

	gameRestarting = true;
	restartTimer = 1.0;
}

int main() {
	
	InitWindow(Constants::screenWidth, Constants::screenHeight, "Pong");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		const auto deltaTime = GetFrameTime();

		restartTimer -= deltaTime;

		switch (gameState)
		{
		case GameState::beginScreen:
			if (IsKeyPressed(KEY_SPACE)) {
				delete player2;
				auto* controlledPlayer = new ControlledPlayer{ Constants::screenWidth - Constants::padding, Constants::screenHeight / 2, KEY_UP, KEY_DOWN };
				player2 = controlledPlayer;
				gameState = GameState::counter;
			}

			else if (IsKeyPressed(KEY_ENTER)) {
				delete player2;
				auto* aiPlayer = new AiPlayer{ Constants::screenWidth - Constants::padding, Constants::screenHeight / 2, &ball};
				player2 = aiPlayer;
				gameState = GameState::counter;
			}

			break;
		case GameState::counter:

			counter -= deltaTime;
			if (counter <= 0.0) {
				// Random y direction
				auto y = GetRandomValue(0, 1) ? GetRandomValue(-10, -5) : GetRandomValue(5, 10);
				// Throw ball in the direction of loser (in the first turn always to the first player) and start a game
				Vector2 direction{player1Won ? 1 : -1, y / 10.0 };
				ball.setDirection(direction);
				gameState = GameState::inProcess;
			}
			break;

		case GameState::inProcess:
			// Increase ball speed each second
			ball.setSpeed(ball.speed() + Constants::ballSpeedIncrease * deltaTime);
			// Update positions
			checkWinConditions();
			player1.move(deltaTime);
			player2->move(deltaTime);
			ball.move(deltaTime);
			// Check collisions with players and borders
			ball.checkCollisions(top, bottom , player1.getRec(), player2->getRec());
			break;
		
		case GameState::gameOver:
			if (restartTimer < 0) {
				player1Won = false;
				gameState = GameState::beginScreen;
			}
		}

		// Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);

		switch (gameState)
		{

		// Draw menu
		case GameState::beginScreen:
			Helpers::DrawCenteredText("Controls:", Constants::screenWidth * 0.1, Constants::screenHeight * 0.05, 20, BLACK);
			Helpers::DrawCenteredText("Player 1 - W/S", Constants::screenWidth * 0.145, Constants::screenHeight * 0.1, 20, BLACK);
			Helpers::DrawCenteredText("Player 2 - Arrow up/down", Constants::screenWidth * 0.23, Constants::screenHeight * 0.15, 20, BLACK);
			Helpers::DrawCenteredText("Press space to play vs player.", Constants::screenWidth / 2, Constants::screenHeight * 0.5, 40, BLACK);
			Helpers::DrawCenteredText("or", Constants::screenWidth / 2, Constants::screenHeight * 0.6, 35, BLACK);
			Helpers::DrawCenteredText("Press enter to play vs ai.", Constants::screenWidth / 2, Constants::screenHeight * 0.7, 40, BLACK);
			break;

		case GameState::counter:
		case GameState::gameOver:
		case GameState::inProcess:

			// Drow counter
			if (gameState == GameState::counter) 
				Helpers::DrawCenteredText(std::to_string(static_cast<int>(ceil(counter))).c_str(), Constants::screenWidth / 2, Constants::screenHeight * 0.1, 40, BLACK);

			else if (gameState == GameState::gameOver) {
				std::string winString = "Player " + std::to_string(player1Won ? 1 : 2) + " won";
				Helpers::DrawCenteredText(winString.c_str(), Constants::screenWidth / 2, Constants::screenHeight * 0.1, 40, BLACK);
			}

			// Draw scores
			else {
				Helpers::DrawCenteredText(std::to_string(static_cast<int>(ceil(player1Score))).c_str(), Constants::screenWidth * 0.4, Constants::screenHeight * 0.1, 40, BLACK);
				Helpers::DrawCenteredText(std::to_string(static_cast<int>(ceil(player2Score))).c_str(), Constants::screenWidth * 0.6, Constants::screenHeight * 0.1, 40, BLACK);
			}
				 
			// Draw entities
			player1.draw();
			player2->draw();
			ball.draw();

			// Draw borders
			DrawRectangle(top.x, top.y, top.width, top.height, Constants::baseColor);
			DrawRectangle(bottom.x, bottom.y, bottom.width, bottom.height, Constants::baseColor);
			break;
		}
		
	
		EndDrawing();
	}

	CloseWindow();

	return 0;
}