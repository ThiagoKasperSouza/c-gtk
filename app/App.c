#include <gtk/gtk.h>
#include <string.h>
#include "./App.h"
#include "../api/helloWorld/helloWorld.c"

struct App {
    GtkApplication *app;
    int status;
};

#define APP_NAME "com.example.myapp"

App* newApp() {
    App* a = (App*) malloc(sizeof(App));
    a->app = gtk_application_new(APP_NAME, 0);
    return a;
}

//#TODO - refatorar activate de modo a estruturar widgets em paginas
static void activate(GtkApplication *app, gpointer user_data) {


    GtkWidget *window,*boxContent1, *boxContent2;
    GtkWidget *button1, *button2;
    GtkWidget *menu_label1, *menu_label2;
    GtkWidget *notebook;


    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 700);

    notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
    gtk_window_set_child(GTK_WINDOW(window), notebook);
    
    boxContent1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    menu_label1 = gtk_label_new("Tab 1"); // Create a menu label widget
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), boxContent1, menu_label1);

    button1 = gtk_button_new_with_label("Hello World 1");
    gtk_widget_set_halign(boxContent1, GTK_ALIGN_START);
    gtk_widget_set_valign(boxContent1, GTK_ALIGN_START);
    g_signal_connect(button1, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_box_append(GTK_BOX(boxContent1), button1);



    boxContent2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    menu_label2 = gtk_label_new("Tab 2"); // Create a menu label widget
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), boxContent2, menu_label2);


    button2 = gtk_button_new_with_label("Hello World 2");
    g_signal_connect(button2, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_box_append(GTK_BOX(boxContent2), button2);


    gtk_window_present(GTK_WINDOW(window));

}

int run(GtkApplication* app, int status) {

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), 0, 0);

    g_object_unref(app);


    return status;
}