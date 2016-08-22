#include <string.h>
#include <gtk/gtk.h>

#include "ui/ui_menubar.h"
#include "ui/ui_tabpkm.h"

static void LoadCss()
{
	GtkCssProvider* provider = gtk_css_provider_new();
	GdkDisplay* display = gdk_display_get_default();
	GdkScreen* screen = gdk_display_get_default_screen(display);

	gtk_style_context_add_provider_for_screen(
		screen,
		GTK_STYLE_PROVIDER(provider),
		GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	const gchar* path = "./style.css";
	gsize written, read;
	GError* error = NULL;
	gtk_css_provider_load_from_path(
		provider,
		g_filename_to_utf8(path, strlen(path), &read, &written, &error),
		NULL);

	g_object_unref(provider);
}

void UI_Main(int argc, char** argv)
{
	gtk_init(&argc, &argv);
	GtkBuilder* builder = gtk_builder_new_from_file("./ui/out.glade");

	GtkWidget* window = GTK_WIDGET(gtk_builder_get_object(builder, "window-main"));
	gtk_window_set_icon_from_file(GTK_WINDOW(window), "icon.png", NULL);
	gtk_builder_connect_signals(builder, NULL);

	UI_Menubar_Setup(builder);
	UI_TabPkm_Setup(builder);

	LoadCss();

	g_object_unref(builder);
	gtk_widget_show_all(window);
	gtk_main();
}