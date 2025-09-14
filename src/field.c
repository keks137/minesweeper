#include "field.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
void genMines(Field *field)
{
	uint32_t minesLeft = field->mines;
	while (minesLeft > 0) {
		uint32_t max_index = (field->width * field->height);
		uint32_t randField = rand() % max_index;
		if (field->fieldnums[randField] != valBomb) {
			field->fieldnums[randField] = valBomb;
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
				if (field->fieldnums[offset_index] == valBomb) {
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
			int32_t *currentField = &field->fieldnums[currentIndex];
			if (*currentField != valBomb) {
				*currentField =
					getOffsetVals(field, widthI, heightI);
			}
		}
	}
}

void printField(Field *field)
{
	for (uint32_t heightI = 0; heightI < field->height; heightI++) {
		for (uint32_t withI = 0; withI < field->width; withI++) {
			int32_t fieldVal =
				field->fieldnums[heightI * field->width + withI];
			if (fieldVal == valBomb) {
				printf("- ");
			} else {
				printf("%i ", fieldVal);
			}
		}
		putc('\n', stdout);
	}
}

