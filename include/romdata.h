#define typeNamesOffset 0x24f1a0
#define learnDataOffset 0x257494

// NOTE! above ones point at bulbasaur, this one points at ???, i.e. pokemon 0.
// I forgot about the "null"-mon before (noticed it in the evolution data, all ids
// being off by 1). from here on, I'll go by mon 0 (and fix the rest as well later).
#define pokemonNamesOffset 0x245ee0
#define pokemonStatsOffset 0x254784
#define evolutionDataOffset 0x259754
#define pointerTableOffset 0x25d7b4 // ptr to/info on learn-by-level-data?
#define moveCompatibilityOffset 0x252bc8

#define moveNamesOffset 0x247094
#define moveDataOffset 0x250c04
