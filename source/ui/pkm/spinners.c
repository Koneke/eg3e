#define SPIN_BUTTON_BASE_PREFIX "pkm-stats-base-"
#define SPIN_BUTTON_EV_PREFIX "pkm-stats-ev-"

#include <string.h>
#include <stdlib.h>

#include <gtk/gtk.h>

#include "common.h"

#include "ui/ui_global.h"
#include "ui/pkm/spinners.h"

#include "model/pokemon.h"

static GtkWidget* base[6];
static GtkWidget* ev[6];

void THIS(setup)()
{
	char* buf = malloc(80);
	for (int i = 0; i < STAT_MAX; i++)
	{
		strcpy(buf, SPIN_BUTTON_BASE_PREFIX);
		strcat(buf, stat_names[i]);
		base[i] = GETS(builder, buf);
		gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(base[i]), gtk_adjustment_new(0, 0, 256, 1, 1, 1));

		strcpy(buf, SPIN_BUTTON_EV_PREFIX);
		strcat(buf, stat_names[i]);
		ev[i] = GETS(builder, buf);
		gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(ev[i]), gtk_adjustment_new(0, 0, 4, 1, 1, 1));
	}
}

void THIS(update)()
{
	for (int i = 0; i < STAT_MAX; i++)
	{
		gtk_spin_button_set_value(
			GTK_SPIN_BUTTON(base[i]),
			0.0 + pokemon_data[pokemon_selected].stats.base[i]);

		gtk_spin_button_set_value(
			GTK_SPIN_BUTTON(ev[i]),
			0.0 + pokemon_getEv(pokemon_data[pokemon_selected].stats.evs, i));
	}
}
