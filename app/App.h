#include <gtk/gtk.h>

#define APP_NAME "com.tks.cgtk"

typedef struct AppEngine AppEngine;

int newApp();
static void activate(GtkApplication *app, gpointer user_data);
