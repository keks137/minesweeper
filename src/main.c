#include "ui.h"
#include <stdbool.h>
#include <raylib.h>
#include <stdint.h>
#include "field.h"
#include "defines.h"

int main()
{
	struct Field GameField = { .height = FIELD_HEIGHT,
				   .width = FIELD_WIDTH,
				   .mines = NUM_MINES };
	Tile fieldbuf[GameField.width * GameField.height] = {};
	GameField.tiles = fieldbuf;
	genMines(&GameField);
	genNums(&GameField);

	UISizes GameUI = {
		.screenWidth = 600,
		.screenHeight = 400,
	};

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(GameUI.screenWidth, GameUI.screenHeight, "Minesweeper");
	// srand(47060);
	// ToggleBorderlessWindowed();
	updateUISizes(&GameUI, &GameField);
	bool gameOver = false;
	while (!WindowShouldClose() && !gameOver) {
		float delta = GetFrameTime();

		if (IsWindowResized()) {
			updateUISizes(&GameUI, &GameField);
		}

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			int mouseX = GetMouseX();
			int mouseY = GetMouseY();
			if (mouseInField(&GameUI, mouseX, mouseY)) {
				Tilepos tilepos = posToTilepos(&GameUI, mouseX, mouseY);
				if (uncoverTile(&GameField, tilepos) == valBomb)
					gameOver = true;
			}
		}

		if (countInvisible(&GameField) == GameField.mines)
			gameOver = true;

		BeginDrawing();
		ClearBackground(DARKGRAY);
		drawVisibleField(&GameUI, &GameField);
		DrawText(TextFormat("FPS: %i", (int)(1.0f / delta)), 0, 0, GameUI.TileContainerY, WHITE);
		EndDrawing();
	}
}
