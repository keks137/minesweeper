#ifndef INCLUDE_SRC_FIELD_H_
#define INCLUDE_SRC_FIELD_H_
#include <stdbool.h>
#include <stdint.h>
enum FieldVals {
	valBomb = -1,
	valEmpty = 0,
};

typedef struct Tile{
	bool visible;
	int32_t val;
}Tile;
typedef struct Field {
	uint32_t mines;
	uint32_t width;
	uint32_t height;
	Tile *tiles;
} Field;

void genMines(Field *field);
int32_t getOffsetVals(Field *field, uint32_t baseX, uint32_t baseY);
void genNums(Field *field);
void printFullField(Field *field);
void printVisibleField(Field *field);
int32_t uncoverTile(Field *field, uint32_t tileX, uint32_t tileY);
uint32_t countInvisible(Field *field);
#endif // INCLUDE_SRC_FIELD_H_
