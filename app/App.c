#include <gtk/gtk.h>
#include <string.h>
#include "./App.h"
#include "../api/helloWorld/helloWorld.c"
#include "../app/pages/MainPage.c"

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

int run(GtkApplication* app, int status) {

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), 0, 0);

    g_object_unref(app);


    return status;
}