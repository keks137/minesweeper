#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "field.h"
#include "defines.h"

int main()
{
	struct Field GameField = { .height = FIELD_HEIGHT,
				   .width = FIELD_WIDTH,
				   .mines = NUM_MINES };
	Tile fieldbuf[GameField.width * GameField.height] = {};
	GameField.fieldnums = fieldbuf;
	srand(47060);
	genMines(&GameField);
	genNums(&GameField);
	bool shouldExit = false;
	while (!shouldExit) {
		printVisibleField(&GameField);
		uint32_t tileX = 0;
		printf("X: ");
		scanf("%d", &tileX);
		uint32_t tileY = 0;
		printf("Y: ");
		scanf("%d", &tileY);

		int32_t val = uncoverTile(&GameField, tileX, tileY);
		if (val == valBomb)
	shouldExit=true;
		printf("was: %i\n", val);
	}
	printFullField(&GameField);
}
