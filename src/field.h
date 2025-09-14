#ifndef INCLUDE_SRC_FIELD_H_
#define INCLUDE_SRC_FIELD_H_
#include <stdint.h>
enum FieldVals {
	valBomb = -1,
	valEmpty = 0,
};

typedef struct Field {
	uint32_t mines;
	uint32_t width;
	uint32_t height;
	int32_t *fieldnums;
} Field;

void genMines(Field *field);
int32_t getOffsetVals(Field *field, uint32_t baseX, uint32_t baseY);
void genNums(Field *field);
void printField(Field *field);
#endif // INCLUDE_SRC_FIELD_H_
