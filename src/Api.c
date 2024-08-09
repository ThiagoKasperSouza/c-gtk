#include <gtk/gtk.h>
#include "App.h"
#include "MainPage.c"
#include "LoginPage.c"

static void print_hello(GtkWidget *widget, gpointer data) {

    g_print("hello world\n");

}

static void print_hello2(GtkWidget *widget, gpointer data) {

    g_print("hello dummy\n");

}

void checar_login(GtkWidget *button, gpointer data) {
    GtkWidget* w = (GtkWidget*) data;
    gtk_window_close(GTK_WINDOW(w));
    runMainPage();
}

void abrir_cadastro(GtkWidget *button, gpointer data) {
     g_print("cadastro");
}

void abrir_recuperar_senha(GtkWidget *button, gpointer data) {
     g_print("recupera senha");
}