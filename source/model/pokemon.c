#include <string.h>
#include <stdio.h> 

#include "global.h"

#include "conversion.h"
#include "romdata.h"
#include "stringutils.h"
#include "fileutils.h"

#include "model/pokemon.h"

#define nameLength 11

void pokemon_load_all()
{
	pokemon_selected = 1; // bulbasaur, not ???

	for (int i = 0; i < PKMN_COUNT; i++)
	{
		pokemon_load(i);
	}
}

void pokemon_load(int id)
{
	int len = 11;
	int offset = pokemonNamesOffset + len * id;
	memset(pokemon_data[id].name, 0, 11);

	fget(romfile, offset, 10, pokemon_data[id].name);
	hexToString(pokemon_data[id].name, 10, pokemon_data[id].name);

	//int len = 28;
	len = 28;
	byte* buf[len];
	fget(romfile, pokemonStatsOffset + len * id, len, buf);
	memcpy(&pokemon_data[id].stats, buf, len);

	len = 40;
	fget(romfile, evolutionDataOffset + len * id, len, buf);
	memcpy(&pokemon_data[id].evolutionData, buf, len);

	len = 4;
	fget(romfile, pointerTableOffset + len * id, len, buf);
	memcpy(&pokemon_data[id].lookup, buf, len);

	len = 8;
	fget(romfile, moveCompatibilityOffset + len * id, len, buf);
	memcpy(&pokemon_data[id].moves, buf, len);
}

int pokemon_getEv(int evs, stat s)
{
	return (evs & (3 << (s * 2))) >> (s * 2);
}
