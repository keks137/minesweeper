#ifndef INCLUDE_SRC_UI_H_
#define INCLUDE_SRC_UI_H_

#include "field.h"
#include <raylib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>



typedef struct UISizes {
	int32_t screenWidth;
	int32_t screenHeight;
	int32_t TileContainerWidth;
	int32_t TileContainerHeight;
	int32_t TileContainerX;
	int32_t TileContainerY;
	int32_t TileSize;
	int32_t TileOffsetX;
	int32_t TileOffsetY;
	bool fillsWidth;
} UISizes;

void updateUISizes(UISizes *UIsizes, Field *field);
void drawFullField(UISizes *UIsizes, Field *field);
void drawVisibleField(UISizes *UIsizes, Field *field);
bool mouseInField(UISizes *UIsizes, int mouseX, int mouseY);
Tilepos posToTilepos(UISizes *UIsizes, int posX, int posY);

#endif // INCLUDE_SRC_UI_H_
