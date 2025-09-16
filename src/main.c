#include "ui.h"
#include <stdbool.h>
#include <raylib.h>
#include <stdint.h>
#include "field.h"
#include "defines.h"
#include <time.h>

void reset(Field *field)
{
	for (int i = 0; i < field->height * field->width; i++) {
		field->tiles[i].visible = false;
		field->tiles[i].val = 0;
	}
	genMines(field, time(NULL));
	genNums(field);
}
int main()
{
	struct Field GameField = { .height = FIELD_HEIGHT,
				   .width = FIELD_WIDTH,
				   .mines = NUM_MINES };
	Tile fieldbuf[FIELD_WIDTH * FIELD_HEIGHT] = {};
	GameField.tiles = fieldbuf;
	genMines(&GameField, time(NULL));
	genNums(&GameField);

	UISizes GameUI = {
		.screenWidth = 1080,
		.screenHeight = 1920,
	};

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(GameUI.screenWidth, GameUI.screenHeight, "Minesweeper");
	SetTargetFPS(60);
	MaximizeWindow();
	updateUISizes(&GameUI, &GameField);
	bool gameOver = false;
	while (!WindowShouldClose() && !gameOver) {
		float delta = GetFrameTime();

		if (IsWindowResized()) {
			updateUISizes(&GameUI, &GameField);
		}

		BeginDrawing();
		ClearBackground(DARKGRAY);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			int mouseX = GetMouseX();
			int mouseY = GetMouseY();
			if (mouseInField(&GameUI, mouseX, mouseY)) {
				Tilepos tilepos = posToTilepos(&GameUI, mouseX, mouseY);
				if (uncoverTile(&GameField, tilepos) == valBomb) {
					ClearBackground(RED);
					reset(&GameField);
				}
			}
		}

		drawVisibleField(&GameUI, &GameField);
		// DrawText(TextFormat("width: %i height: %i", GameUI.screenWidth, GameUI.screenHeight), 0, 0, GameUI.TileContainerY, WHITE);
		if (countInvisible(&GameField) == GameField.mines) {
			DrawText(TextFormat("You Win!", (int)(1.0f / delta)), 0, 0, GameUI.TileContainerY, GOLD);
			reset(&GameField);
		}
		EndDrawing();
	}
}
