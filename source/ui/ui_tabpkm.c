#include "ui/ui_global.h"
#include "model/pokemon.h"

static GtkWidget* base_hp;
static GtkWidget* base_atk;
static GtkWidget* base_def;
static GtkWidget* base_spa;
static GtkWidget* base_spd;
static GtkWidget* base_spe;
static GtkWidget* ev_hp;
static GtkWidget* ev_atk;
static GtkWidget* ev_def;
static GtkWidget* ev_spa;
static GtkWidget* ev_spd;
static GtkWidget* ev_spe;

static void updateSpinners()
{
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(base_hp),  0.0 + pokemon_data[pokemon_selected].stats.hp);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(base_atk), 0.0 + pokemon_data[pokemon_selected].stats.atk);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(base_def), 0.0 + pokemon_data[pokemon_selected].stats.def);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(base_spa), 0.0 + pokemon_data[pokemon_selected].stats.spa);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(base_spd), 0.0 + pokemon_data[pokemon_selected].stats.spd);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(base_spe), 0.0 + pokemon_data[pokemon_selected].stats.spe);

	gtk_spin_button_set_value(GTK_SPIN_BUTTON(base_spe), 0.0 + pokemon_data[pokemon_selected].stats.spe);
}

static void list_onSelection(GtkTreeSelection* selection, gpointer data)
{
	GtkTreeIter iter;
	GtkTreeModel* model;
	gint number;

	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gtk_tree_model_get(model, &iter, 0, &number, -1);
		pokemon_selected = number;
		updateSpinners();
		g_print("selected number %i\n", number);
	}
}

static GtkListStore* list;

static void AddRow(int number, const char* name)
{
	GtkTreeIter iter;
	gtk_list_store_insert(list, &iter, -1);
	gtk_list_store_set(list, &iter, 0, number, 1, name, -1);
}

static GtkWidget* createTreeView()
{
	GtkWidget* treeview = gtk_tree_view_new();
	gtk_widget_set_size_request(GTK_WIDGET(treeview), 100, -1);

	GtkTreeSelection* selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	g_signal_connect(selection, "changed", G_CALLBACK(list_onSelection), NULL);

	GtkCellRenderer* renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "#", renderer, "text", 0, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "Name", renderer, "text", 1, NULL);

	return treeview;
}

static GtkTreeModel* createModel()
{
	GtkTreeModel* model;
	GtkTreeIter iter;
	list = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);

	model = GTK_TREE_MODEL(list);
	return model;
}

static void setupSpinners()
{
	base_hp =  GET(builder, pkm-stats-base-hp);
	base_atk = GET(builder, pkm-stats-base-atk);
	base_def = GET(builder, pkm-stats-base-def);
	base_spa = GET(builder, pkm-stats-base-spa);
	base_spd = GET(builder, pkm-stats-base-spd);
	base_spe = GET(builder, pkm-stats-base-spe);
	ev_hp =  GET(builder, pkm-stats-ev-hp);
	ev_atk = GET(builder, pkm-stats-ev-atk);
	ev_def = GET(builder, pkm-stats-ev-def);
	ev_spa = GET(builder, pkm-stats-ev-spa);
	ev_spd = GET(builder, pkm-stats-ev-spd);
	ev_spe = GET(builder, pkm-stats-ev-spe);
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(base_hp),  gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(base_atk), gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(base_def), gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(base_spa), gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(base_spd), gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(base_spe), gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(ev_hp),  gtk_adjustment_new(0, 0, 4, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(ev_atk), gtk_adjustment_new(0, 0, 4, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(ev_def), gtk_adjustment_new(0, 0, 4, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(ev_spa), gtk_adjustment_new(0, 0, 4, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(ev_spd), gtk_adjustment_new(0, 0, 4, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(ev_spe), gtk_adjustment_new(0, 0, 4, 1, 1, 1));
}

void UI_TabPkm_Setup()
{
	GtkWidget* hbox = GET(builder, pkm-hbox);

	GtkWidget* treeview = createTreeView();
	GtkTreeModel* model = createModel();

	AddRow(1, "Bulbasaur");

	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
	g_object_unref(model);

	setupSpinners();

	gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(treeview), FALSE, FALSE, 0);
}
