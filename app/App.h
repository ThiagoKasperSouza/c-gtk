#include <gtk/gtk.h>

typedef struct App App;

App* newApp();
static void activate(GtkApplication *app, gpointer user_data);
int run();