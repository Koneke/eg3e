#pragma once
#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;
// endianness words
typedef struct { uint8_t ls; uint8_t ms; } leword;
typedef struct { uint8_t ms; uint8_t ls; } beword;

typedef enum {
	hp, atk, def, spe, spa, spd
} stat;
