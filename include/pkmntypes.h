#pragma once

typedef struct {
	int hp;
	int atk;
	int def;
	int spa;
	int spd;
	int spe;
} stats;

typedef struct {
	char name[10];
	stats stats;
} pokemon;

char charHexValue[0xff] = {
	[numbersStart] =
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	[alphabetStart] =
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};
