#include <gtk/gtk.h>

#define GET(x, y) GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(x), #y))

static void list_onSelection(GtkWidget* widget, gpointer data)
{
	g_print("test\n");
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

static void setupSpinners(GtkBuilder* builder)
{
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-base-hp)),  gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-base-atk)), gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-base-def)), gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-base-spa)), gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-base-spd)), gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-base-spe)), gtk_adjustment_new(0, 0, 256, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-ev-hp)),  gtk_adjustment_new(0, 0, 4, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-ev-atk)), gtk_adjustment_new(0, 0, 4, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-ev-def)), gtk_adjustment_new(0, 0, 4, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-ev-spa)), gtk_adjustment_new(0, 0, 4, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-ev-spd)), gtk_adjustment_new(0, 0, 4, 1, 1, 1));
	gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(GET(builder, pkm-stats-ev-spe)), gtk_adjustment_new(0, 0, 4, 1, 1, 1));
}

void UI_TabPkm_Setup(GtkBuilder* builder)
{
	GtkWidget* hbox = GET(builder, pkm-hbox);

	GtkWidget* treeview = createTreeView();
	GtkTreeModel* model = createModel();

	AddRow(1, "Fletchinder");

	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
	g_object_unref(model);

	setupSpinners(builder);

	gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(treeview), FALSE, FALSE, 0);
}
