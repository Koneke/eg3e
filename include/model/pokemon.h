#pragma once
#include "typedefs.h"

#define PKMN_COUNT 412

typedef enum { STAT_HP, STAT_ATK, STAT_DEF, STAT_SPE, STAT_SPA, STAT_SPD, STAT_MAX } stat;

typedef struct {
/* 01 */	uint8_t base[6];
/* 07 */	uint8_t typeA;
/* 08 */	uint8_t typeB;
/* 09 */	uint8_t catchRate;
/* 10 */	uint8_t baseExp;
/* 11 */	uint16_t evs; // 2 bits per stat
/* 17 */	uint16_t itemA;
/* 18 */	uint16_t itemB;
/* 19 */	uint8_t genderRatio;
/* 20 */	uint8_t eggHatchCycles;
/* 21 */	uint8_t baseHappiness;
/* 22 */	uint8_t growthRate;
/* 23 */	uint8_t eggGroupA;
/* 24 */	uint8_t eggGroupB;
/* 25 */	uint8_t abilityA;
/* 26 */	uint8_t abilityB;
/* 27 */	uint8_t safariRunRate;
/* 28 */	uint8_t misc;
				// highbits - facing direction on status screen
				// lowbits - pokedex colour
/* 29 */	uint8_t padding; // always 0
} stats;

typedef struct {
	leword learningDataOffset; // relative to 0x250000
	uint16_t misc; // always 0x825?? weird
} ptrTable;

typedef struct {
	uint16_t method;
	uint16_t parameter;
	uint16_t target;
	uint16_t pad;
} evolutionDataSubstructure;

typedef struct {
	evolutionDataSubstructure evolutions[5];
	uint32_t padding;
} evolutionData;

typedef struct {
	char name[11];
	stats stats;
	evolutionData evolutionData;
	ptrTable lookup;
	uint64_t moves;
} pokemon;

int pokemon_selected;
pokemon pokemon_data[PKMN_COUNT];

void pokemon_load_all();
void pokemon_load(int id);
int pokemon_getEv(int evs, stat s);
