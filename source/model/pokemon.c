#include <string.h>
#include <stdio.h> 

#include "global.h"

#include "conversion.h"
#include "romdata.h"
#include "stringutils.h"
#include "fileutils.h"

#include "model/pokemon.h"

#define nameLength 11

void load(int id)
{
	int offset = pokemonNamesOffset + nameLength * id;
	memset(pokemonData[id].name, 0, 11);

	fget(romfile, offset, 10, pokemonData[id].name);
	hexToString(pokemonData[id].name, 10, pokemonData[id].name);

	int len = 28;
	byte* buf[len];
	fget(romfile, pokemonStatsOffset + len * id, len, buf);
	memcpy(&pokemonData[id].stats, buf, len);

	len = 40;
	fget(romfile, evolutionDataOffset + len * id, len, buf);
	memcpy(&pokemonData[id].evolutionData, buf, len);

	len = 4;
	fget(romfile, pointerTableOffset + len * id, len, buf);
	memcpy(&pokemonData[id].lookup, buf, len);

	len = 8;
	fget(romfile, moveCompatibilityOffset + len * id, len, buf);
	memcpy(&pokemonData[id].moves, buf, len);
}
