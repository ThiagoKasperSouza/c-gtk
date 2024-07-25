#include <gtk/gtk.h>
#include "./TabMenu.h"


GtkWidget newTabMenu(GtkWidget* window, GtkWidget* *notebook) {
    *notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
    gtk_window_set_child(GTK_WINDOW(window), notebook);
    return notebook;
}

void appendPage(GtkWidget* notebook, GtkWidget* child, char* label) {
    child = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget* menu_label = gtk_label_new(label); // Create a menu label widget
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),child, menu_label);
}
