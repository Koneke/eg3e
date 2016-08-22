#include "common.h"

#include "string.h"
#include "stdlib.h"

#include "model/pokemon.h"
#include "ui/ui_global.h"

#include "ui/pkm/namebox.h"
#include "ui/pkm/spinners.h"
#include "ui/pkm/comboboxes.h"

#undef MODULE_NAME
#define MODULE_NAME pkm

static void THIS(update)()
{
	THIS(spinners_update)();
	THIS(comboboxes_update)();
	THIS(namebox_update)();
}

// tree view
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
		return GTK_TREE_MODEL(list = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING));
	}

void UI_TabPkm_Setup()
{
	GtkWidget* hbox = GET(builder, pkm-hbox);

	GtkWidget* treeview = createTreeView();
	GtkTreeModel* model = createModel();

	AddRow(1, "Bulbasaur");

	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
	g_object_unref(model);

	pkm_spinners_setup();
	pkm_comboboxes_setup();
	pkm_namebox_setup();

	gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(treeview), FALSE, FALSE, 0);
}
