#include <gtk/gtk.h>

#include "ui/ui_global.h"
#include "ui/pkm/pkm.h"
#include "ui/pkm/pkmlist.h"

#include "model/pokemon.h"

static GtkWidget* treeview;
static GtkListStore* list;

static void list_onSelection(GtkTreeSelection* selection, gpointer data)
{
	GtkTreeIter iter;
	GtkTreeModel* model;
	gint number;

	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gtk_tree_model_get(model, &iter, 0, &number, -1);
		pokemon_selected = number;

		pkm_update();
	}
}

static void addRow(int number, const char* name)
{
	GtkTreeIter iter;
	gtk_list_store_insert(list, &iter, -1);
	gtk_list_store_set(list, &iter, 0, number, 1, name, -1);
}

static GtkTreeModel* createModel()
{
	return GTK_TREE_MODEL(list = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING));
}

static GtkWidget* createTreeView()
{
	treeview = gtk_tree_view_new();
	gtk_widget_set_size_request(GTK_WIDGET(treeview), 100, -1);

	GtkTreeSelection* selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	g_signal_connect(selection, "changed", G_CALLBACK(list_onSelection), NULL);

	GtkCellRenderer* renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "#", renderer, "text", 0, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "Name", renderer, "text", 1, NULL);

	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), createModel());

	return treeview;
}

static void addTreeView()
{
	//GtkWidget* hbox = GET(builder, pkm-hbox);
	//gtk_box_pack_start(
	gtk_container_add(
		GTK_CONTAINER(GET(builder, pkm-pkmlist-container)),
		GTK_WIDGET(treeview));
		//FALSE, FALSE, 0);
}

static void load()
{
	for (int i = 1; i < PKMN_COUNT; i++)
	{
		addRow(i, pokemon_data[i].name);
	}
}

void THIS(setup)()
{
	createTreeView();
	addTreeView();
	load();

	//addRow(1, "Bulbasaur");
}
