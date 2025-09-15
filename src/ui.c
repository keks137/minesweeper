#include "ui.h"
#include <raylib.h>
#include <stddef.h>
#include <stdint.h>

// 0 there for proper indexing
Color textColors[9] = { RED, BLUE, GREEN, RED, ORANGE, PURPLE, MAROON, GOLD, BLACK };
const char *numberChars[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8" };
int textWidths[9] = {};

void updateUISizes(UISizes *UIsizes, Field *field)
{
	UIsizes->screenWidth = GetScreenWidth();
	UIsizes->screenHeight = GetScreenHeight();
	UIsizes->TileContainerWidth = UIsizes->screenWidth - UIsizes->screenWidth / 10;
	UIsizes->TileContainerHeight = UIsizes->screenHeight - UIsizes->screenHeight / 10;
	UIsizes->TileContainerX = UIsizes->screenWidth / 2 - UIsizes->TileContainerWidth / 2;
	UIsizes->TileContainerY = UIsizes->screenHeight / 2 - UIsizes->TileContainerHeight / 2;
	float widthRatio = (float)UIsizes->TileContainerWidth / (float)field->width;
	float heightRatio = (float)UIsizes->TileContainerHeight / (float)field->height;
	if (widthRatio < heightRatio) {
		UIsizes->TileSize = (int32_t)widthRatio;
		UIsizes->fillsWidth = true;
		UIsizes->TileOffsetX = 0;
		UIsizes->TileOffsetY = (UIsizes->TileContainerHeight - UIsizes->TileSize * field->height) / 2;
	} else {
		UIsizes->TileSize = (int32_t)heightRatio;
		UIsizes->fillsWidth = false;
		UIsizes->TileOffsetY = 0;
		UIsizes->TileOffsetX = (UIsizes->TileContainerWidth - UIsizes->TileSize * field->width) / 2;
	}
	for (uint32_t i = 0; i < (uint32_t)(sizeof(textWidths) / sizeof(textWidths[0])); i++) {
		textWidths[i] = MeasureText(numberChars[i], UIsizes->TileSize);
	}
}

void drawFullField(UISizes *UIsizes, Field *field)
{
	for (uint32_t y = 0; y < field->height; y++) {
		for (uint32_t x = 0; x < field->width; x++) {
			int32_t val = field->tiles[x + y * field->width].val;
			Color tileColor = (val == valBomb) ? RED : LIGHTGRAY;
			const int recX = UIsizes->TileContainerX + UIsizes->TileOffsetX + x * UIsizes->TileSize;
			const int recY = UIsizes->TileContainerY + UIsizes->TileOffsetY + y * UIsizes->TileSize;
			DrawRectangleLines(recX, recY, UIsizes->TileSize, UIsizes->TileSize, DARKGRAY);
			DrawRectangle(recX, recY, UIsizes->TileSize, UIsizes->TileSize, tileColor);
			if (val > 0) {
				DrawText(numberChars[val], UIsizes->TileContainerX + UIsizes->TileOffsetX + x * UIsizes->TileSize + (UIsizes->TileSize - textWidths[val]) / 2, UIsizes->TileContainerY + UIsizes->TileOffsetY + y * UIsizes->TileSize, UIsizes->TileSize, textColors[val]);
			}
		}
	}
}

void drawVisibleField(UISizes *UIsizes, Field *field)
{
	for (uint32_t y = 0; y < field->height; y++) {
		for (uint32_t x = 0; x < field->width; x++) {
			Tile tile = field->tiles[x + y * field->width];
			const int recX = UIsizes->TileContainerX + UIsizes->TileOffsetX + x * UIsizes->TileSize;
			const int recY = UIsizes->TileContainerY + UIsizes->TileOffsetY + y * UIsizes->TileSize;
			DrawRectangleLines(recX, recY, UIsizes->TileSize, UIsizes->TileSize, DARKGRAY);
			if (tile.visible) {
				int32_t val = tile.val;
				Color tileColor = (val == valBomb) ? RED : LIGHTGRAY;
				DrawRectangle(recX, recY, UIsizes->TileSize, UIsizes->TileSize, tileColor);
				if (val > 0) {
					DrawText(numberChars[val], UIsizes->TileContainerX + UIsizes->TileOffsetX + x * UIsizes->TileSize + (UIsizes->TileSize - textWidths[val]) / 2, UIsizes->TileContainerY + UIsizes->TileOffsetY + y * UIsizes->TileSize, UIsizes->TileSize, textColors[val]);
				}
			} else {
				DrawRectangle(recX, recY, UIsizes->TileSize, UIsizes->TileSize, GRAY);
			}
		}
	}
}

bool mouseInField(UISizes *UIsizes, int mouseX, int mouseY)
{
	if (mouseX >= UIsizes->TileContainerX + UIsizes->TileOffsetX && mouseX <= UIsizes->TileContainerX + UIsizes->TileContainerWidth - UIsizes->TileOffsetX && mouseY >= UIsizes->TileContainerY + UIsizes->TileOffsetY && mouseY <= UIsizes->TileContainerY + UIsizes->TileContainerHeight - UIsizes->TileOffsetY)
		return true;
	return false;
}

Tilepos posToTilepos(UISizes *UIsizes, int posX, int posY)
{
	uint32_t fieldX = posX - (UIsizes->TileContainerX + UIsizes->TileOffsetX);
	uint32_t fieldY = posY - (UIsizes->TileContainerY + UIsizes->TileOffsetY);
	Tilepos tile;
	tile.x = fieldX / UIsizes->TileSize;
	tile.y = fieldY / UIsizes->TileSize;
	return tile;
}
