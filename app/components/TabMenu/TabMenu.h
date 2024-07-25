#include <gtk/gtk.h>

//https://docs.gtk.org/gtk4/class.Notebook.html
typedef struct TabMenu TabMenu;
void newTabMenu(GtkWidget* window, GtkWidget* *notebook);
void appendPage(GtkWidget* notebook,GtkWidget* child,char* label);