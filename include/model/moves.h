#include "typedefs.h"

typedef struct {
	uint8_t effect;
	uint8_t basePower;
	uint8_t type;
	uint8_t accuracy;
	uint8_t pp;
	uint8_t effectAccuracy;
	uint8_t target;
	uint8_t priority;
	uint8_t flags;
	//
	uint16_t pad;
	uint8_t padd;
} s_moveData;

typedef struct {
	char name[14];
	s_moveData data;
} s_move;
