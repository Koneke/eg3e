#pragma once
#include <gtk/gtk.h>

#define GET(x, y) GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(x), #y))
#define GETS(x, y) GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(x), y))
#define NWGET(x, y) gtk_builder_get_object(GTK_BUILDER(x), #y)

#define PASTER(x,y) x ## _ ## y
#define PASTE(x,y) PASTER(x,y)
#define THIS(x) PASTE(MODULE_NAME, x) 

GtkBuilder* builder;
