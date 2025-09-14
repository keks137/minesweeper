#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "field.h"
#include "defines.h"

int32_t uncoverTile(Field *field, uint32_t tileX, uint32_t tileY)
{
	uint32_t currentIndex = tileX + tileY * field->width;
	int32_t val = field->fieldnums[currentIndex];
	return val;
}
int main()
{
	struct Field GameField = { .height = FIELD_HEIGHT,
				   .width = FIELD_WIDTH,
				   .mines = NUM_MINES };
	int32_t fieldbuf[GameField.width * GameField.height] = {};
	GameField.fieldnums = fieldbuf;
	srand(47060);
	genMines(&GameField);
	genNums(&GameField);
	printField(&GameField);
	bool shouldExit = false;
	while (!shouldExit) {
		uint32_t tileX = 0;
		printf("X: ");
		scanf("%d", &tileX);
		uint32_t tileY = 0;
		printf("Y: ");
		scanf("%d", &tileY);

		int32_t val = uncoverTile(&GameField, tileX, tileY);
		if (val == valBomb)
			exit(0);
		printf("%i\n", val);
	}
}
