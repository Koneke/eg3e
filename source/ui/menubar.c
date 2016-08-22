#include "ui/ui_global.h"

void UI_Menubar_Setup()
{
	GtkWidget* menubar = GET(builder, menubar); //GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder), "menubar"));
	GtkWidget* fileMenu = gtk_menu_new();
	GtkWidget* file = gtk_menu_item_new_with_label("File");
	GtkWidget* open = gtk_menu_item_new_with_label("Open");
	GtkWidget* quit = gtk_menu_item_new_with_label("Quit");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), fileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), open);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quit);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
}
