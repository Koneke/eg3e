#include "common.h"

#include "string.h"
#include "stdlib.h"

#include "model/pokemon.h"
#include "ui/ui_global.h"

#include "ui/pkm/pkmlist.h"
#include "ui/pkm/namebox.h"
#include "ui/pkm/spinners.h"
#include "ui/pkm/comboboxes.h"
#include "ui/pkm/pkm.h"

void THIS(update)()
{
	THIS(spinners_update)();
	THIS(comboboxes_update)();
	THIS(namebox_update)();
}

void THIS(setup)()
{
	THIS(pkmlist_setup)();
	THIS(spinners_setup)();
	THIS(comboboxes_setup)();
	THIS(namebox_setup)();
}
