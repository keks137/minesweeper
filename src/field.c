#include "field.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
void genMines(Field *field)
{
	uint32_t minesLeft = field->mines;
	while (minesLeft > 0) {
		uint32_t max_index = (field->width * field->height);
		uint32_t randField = rand() % max_index;
		if (field->tiles[randField].val != valBomb) {
			field->tiles[randField].val = valBomb;
			minesLeft--;
		}
	}
}

int32_t getOffsetVals(Field *field, uint32_t baseX, uint32_t baseY)
{
	int32_t neighborOffsetX[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	int32_t neighborOffsetY[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int32_t fieldVal = 0;
	for (uint32_t offI = 0; offI < 8; offI++) {
		int32_t neighborX = baseX + neighborOffsetX[offI];
		int32_t neighborY = baseY + neighborOffsetY[offI];
		if (neighborX >= 0 && (uint32_t)neighborX < field->width) {
			if (neighborY >= 0 &&
			    (uint32_t)neighborY < field->height) {
				int32_t offset_index =
					neighborX + neighborY * field->width;
				if (field->tiles[offset_index].val == valBomb) {
					fieldVal++;
				}
			}
		}
	}
	return fieldVal;
}
void genNums(Field *field)
{
	for (uint32_t heightI = 0; heightI < field->height; heightI++) {
		for (uint32_t widthI = 0; widthI < field->width; widthI++) {
			uint32_t currentIndex = heightI * field->width + widthI;
			int32_t *currentField = &field->tiles[currentIndex].val;
			if (*currentField != valBomb) {
				*currentField =
					getOffsetVals(field, widthI, heightI);
			}
		}
	}
}

void printFullField(Field *field)
{
	for (uint32_t heightI = 0; heightI < field->height; heightI++) {
		for (uint32_t withI = 0; withI < field->width; withI++) {
			int32_t fieldVal =
				field->tiles[heightI * field->width + withI].val;
			if (fieldVal == valBomb) {
				printf("- ");
			} else {
				printf("%i ", fieldVal);
			}
		}
		putc('\n', stdout);
	}
}

void printVisibleField(Field *field)
{
	for (uint32_t heightI = 0; heightI < field->height; heightI++) {
		for (uint32_t withI = 0; withI < field->width; withI++) {
			Tile tile =
				field->tiles[heightI * field->width + withI];
			if (tile.visible) {
				if (tile.val == valBomb) {
					printf("- ");
				} else {
					printf("%i ", tile.val);
				}
			} else {
				printf("  ");
			}
		}
		putc('\n', stdout);
	}
}
void uncoverFlood(Field *field, uint32_t tileX, uint32_t tileY)
{
	struct xandy {
		uint32_t x;
		uint32_t y;
	};
	const uint32_t tileIndexBufSize = 2048;
	struct xandy tileIndexBuf[tileIndexBufSize];
	size_t tileIndexBufLevel = 0;
	size_t tileIndexBufCurrent = 0;

	tileIndexBuf[0].x = tileX;
	tileIndexBuf[0].y = tileY;
	tileIndexBufLevel++;

	int32_t neighborOffsetX[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	int32_t neighborOffsetY[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	while (tileIndexBufCurrent < tileIndexBufLevel) {
		for (uint32_t offI = 0; offI < 8; offI++) {
			int32_t neighborX =
				tileIndexBuf[tileIndexBufCurrent].x +
				neighborOffsetX[offI];
			int32_t neighborY =
				tileIndexBuf[tileIndexBufCurrent].y +
				neighborOffsetY[offI];
			if (neighborX >= 0 &&
			    (uint32_t)neighborX < field->width) {
				if (neighborY >= 0 &&
				    (uint32_t)neighborY < field->height) {
					int32_t offset_index =
						neighborX +
						neighborY * field->width;
					Tile *current_tile =
						&field->tiles[offset_index];
					if (!field->tiles[offset_index].visible) {
						current_tile->visible = true;
						if (current_tile->val ==
						    valEmpty) {
							if (tileIndexBufLevel <
							    tileIndexBufSize) {
								tileIndexBuf[tileIndexBufLevel]
									.x =
									neighborX;
								tileIndexBuf[tileIndexBufLevel]
									.y =
									neighborY;
								tileIndexBufLevel++;

							} else {
								return;
							}
						}
					}
				}
			}
		}
		tileIndexBufCurrent++;
	}
}
int32_t uncoverTile(Field *field, uint32_t tileX, uint32_t tileY)
{
	uint32_t currentIndex = tileX + tileY * field->width;
	int32_t val = field->tiles[currentIndex].val;
	field->tiles[currentIndex].visible = true;
	if (val == 0)
		uncoverFlood(field, tileX, tileY);
	return val;
}
