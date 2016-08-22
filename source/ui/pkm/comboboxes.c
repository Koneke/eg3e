#include <gtk/gtk.h>

#include "common.h"

#include "ui/ui_global.h"
#include "ui/pkm/comboboxes.h"

#include "model/pokemon.h"

static GtkWidget* type[2];
static GtkWidget* ability[2];

void THIS(setup)()
{
	type[0] = GET(builder, pkm-stats-typeA);
	type[1] = GET(builder, pkm-stats-typeB);
	ability[0] = GET(builder, pkm-stats-abilityA);
	ability[1] = GET(builder, pkm-stats-abilityB);

	for (int i = 0; i < 19; i++)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(type[0]), types[i]);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(type[1]), types[i]);
	}
}

void THIS(update)()
{
	gtk_combo_box_set_active(GTK_COMBO_BOX(type[0]), pokemon_data[pokemon_selected].stats.typeA);
	gtk_combo_box_set_active(GTK_COMBO_BOX(type[1]), pokemon_data[pokemon_selected].stats.typeB);
}
