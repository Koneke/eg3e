#include <gtk/gtk.h>

#include "ui/ui_global.h"
#include "ui/pkm/namebox.h"

#include "model/pokemon.h"

static GtkWidget* nameBox;

void THIS(setup)()
{
	nameBox = GET(builder, pkm-name);
}

void THIS(update)()
{
	gtk_entry_set_text(GTK_ENTRY(nameBox), pokemon_data[pokemon_selected].name);
}
