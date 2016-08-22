#include <stdarg.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#include "global.h"

#include "stringutils.h"
#include "fileutils.h"

#include "model/pokemon.h"
#include "model/moves.h"

#include "typedefs.h"
#include "romdata.h"
#include "conversion.h"

#include <gtk/gtk.h>
#include "ui/ui_main.h"

#define nameLength 11

void learningData()
{
	int c = 30;
	int id = 1;
	byte* buf = malloc(c * 2);
	{
		fget(romfile, learnDataOffset, c * 2, buf);

		for (int i = 0; i < c; i++)
		{
			printf("%u - %u %u\n", id, buf[i * 2], buf[i * 2 + 1]);
			if (buf[i * 2] == 0xff) id++;
		}
	}
	free(buf);
}

int main(int argc, char** argv)
{
	if ((romfile = fopen("./clone.GBA", "r+")) == NULL)
	{
		printf("couldn't find clone.gba\n");
		return 1;
	}

	pokemon_load_all();

	UI_Main(argc, argv);

	/*loadMoves();

	for (int i = 0; i < MOVE_COUNT; i++)
	{
		s_moveData md = moveData[i].data;
		//if (md.effect == 0x00) continue;

		printf(
			//"%s %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
			"%02x %s" "\n",
			md.effect,
			moveData[i].name,
			md.basePower, md.type, md.accuracy, md.pp,
			md.effectAccuracy, md.target, md.priority, md.flags);
	}

	int bufSize = 200;
	char* buf = malloc(bufSize * sizeof(char));
	{
		for (int i = 0; i < PKMN_COUNT; i++)
		{
			pokemon* p = &pokemonData[i];
			load(i);
			//printf("%s %08u %08u\n", p->name, p->lookup.learningDataOffset, p->lookup.misc);
			printf("%s %u\n",
				p->name,
				p->moves
			);
			//printPokemon(buf, "%0s %20u\n", &pokemonData[i]);
		}
	}
	free(buf);*/

	fclose(romfile);
	return 0;
}
