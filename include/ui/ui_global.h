#pragma once
#include <gtk/gtk.h>

#define GET(x, y) GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(x), #y))

GtkBuilder* builder;
