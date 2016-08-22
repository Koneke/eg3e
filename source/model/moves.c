#include "global.h" 

#include <stdlib.h> 
#include <string.h>

#include "romdata.h"
#include "model/moves.h"

#include "typedefs.h"
#include "conversion.h"
#include "fileutils.h"

#define MOVE_COUNT 355

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

s_move moveData[MOVE_COUNT];

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
