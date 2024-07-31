#include <gtk/gtk.h>

//https://docs.gtk.org/gtk4/class.Notebook.html
typedef struct Tab Tab;
typedef struct TabMenu TabMenu;

TabMenu* newTabMenu(GtkWidget *window, struct Tab *tabs);
void freeTabMenu(struct TabMenu *mainContainer);