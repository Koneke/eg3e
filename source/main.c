#include <stdarg.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#include "global.h"

#include "stringutils.h"
#include "fileutils.h"

#include "model/pokemon.h"
#include "model/move.h"

#include "typedefs.h"
#include "romdata.h"
#include "conversion.h"

#include <gtk/gtk.h>
#include "ui/ui_main.h"

/* (evolution methods)
// 00 - none
// 01 - friendship
// 02 - friendship during the day
// 03 - friendship during the night
// 04 - level
// 05 - trade
// 06 - trade with item
// 07 - stone
// 08 - def < atk
// 09 - def = atk
// 10 - def > atk

// NINJASK BULLSHIT AHEAD
// 11 - personality value
// 12 - personality value
// 13 - may spawn additional
// 14 - additionally spawned

// 15 - beauty */

const char* types[18] = {
	"Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel",
	"???", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark"
};

#define MOVE_COUNT 355

s_move moveData[MOVE_COUNT];

#define nameLength 11

/*static void load(int id)
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
}*/

int getEv(int evs, stat s)
{
	return (evs & (3 << (s * 2))) >> (s * 2);
}

void printPokemon(char* buf, char* fmt, pokemon *p)
{
	stats* s = &p->stats;
	eprintf(buf, fmt, 31,
		p->name,
		s->hp, s->atk, s->def, s->spe, s->spa, s->spd,
		types[s->typeA], types[s->typeB], 
		s->catchRate,
		s->baseExp,
		getEv(s->evs, hp),
		getEv(s->evs, atk),
		getEv(s->evs, def),
		getEv(s->evs, spe),
		getEv(s->evs, spa),
		getEv(s->evs, spd),
		s->itemA,
		s->itemB,
		s->genderRatio,
		s->eggHatchCycles,
		s->baseHappiness,
		s->growthRate,
		s->eggGroupA,
		s->eggGroupB,
		s->abilityA,
		s->abilityB,
		s->safariRunRate,
		s->misc,
		s->padding
	);
	printf("%s", buf);
}

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

enum eMoves
{
	FocusPunch,  // ----      |
	DragonClaw,  //           | More significant
	WaterPulse,  //           |
	CalmMind,    // BYTE 1    V
	Roar,        //
	Toxic,       //
	Hail,        //
	BulkUp,      // ----
	BulletSeed,  // ----
	HiddenPower, //
	SunnyDay,    //
	Taunt,       // BYTE 2
	IceBeam,     //
	Blizzard,    //
	HyperBeam,   //
	LightScreen, // ----
	Protect,     // ----
	RainDance,   //
	GigaDrain,   //
	Safeguard,   // BYTE 3
	Frustration, //
	Solarbeam,   //
	IronTail,    //
	Thunderbolt, // ----
	Thunder,     // ----
	Earthquake,  //
	Return,      //
	Dig,         // BYTE 4
	Psychic,     //
	ShadowBall,  //
	BrickBreak,  //
	DoubleTeam,  // ----
	Reflect,     // ----
	ShockWave,   //
	Flamethrower,//
	SludgeBomb,  // BYTE 5
	Sandstorm,   //
	FireBlast,   //
	RockTomb,    //
	AerialAce,   // ----
	Torment,     // ----
	Facade,      //
	SecretPower, //
	Rest,        // BYTE 6
	Attract,     //
	Thief,       //
	SteelWing,   //
	SkillSwap,   // ----
	Snatch,      // ----
	Overheat,    // 
	Cut,         //
	Fly,         // BYTE 7
	Surf,        //
	Strength,    //
	Flash,       //
	RockSmash,   // ----
	Waterfall,   // ----
	Dive         // BYTE 8
};

void printFlags(char* out, uint8_t flags)
{
	char sbuf[16];
	sprintf(sbuf, "%u %u %u %u %u %u %u %u",
		flags >> 0 & 1,
		flags >> 1 & 1,
		flags >> 2 & 1,
		flags >> 3 & 1,
		flags >> 4 & 1,
		flags >> 5 & 1,
		flags >> 6 & 1,
		flags >> 7 & 1);
	memcpy(out, sbuf, 15);
}

void loadMoves()
{
	//static uint8_t buf[4096];
	int moves = MOVE_COUNT;
	int len = 12;

	uint8_t* dbuf = malloc(moves * len);
	{
		fget(romfile, moveDataOffset, moves * len, dbuf);
		for (int i = 0; i < moves; i++)
		{
			memcpy(&moveData[i].data, dbuf + i * len, len);
		}
	}
	free(dbuf);

	len = 13;
	char* sbuf = malloc(moves * len);
	{
		fget(romfile, moveNamesOffset, moves * len, sbuf);

		for (int i = 0; i < moves; i++)
		{
			memset(moveData[i].name, 0, len + 1);
			memcpy(moveData[i].name, dbuf + i * len, len);
			hexToString(moveData[i].name, len, moveData[i].name);
		}
	}
	free(sbuf);
}

int main(int argc, char** argv)
{
	if ((romfile = fopen("./clone.GBA", "r+")) == NULL)
	{
		printf("couldn't find clone.gba\n");
		return 1;
	}

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
