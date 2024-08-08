#include <gtk/gtk.h>
#include "App.h"

static void print_hello(GtkWidget *widget, gpointer data) {

    g_print("hello world\n");

}

static void print_hello2(GtkWidget *widget, gpointer data) {

    g_print("hello dummy\n");

}

void checar_login(GtkWidget *button, gpointer data) {
    g_print("login");
}

void abrir_cadastro(GtkWidget *button, gpointer data) {
     g_print("cadastro");
}

void abrir_recuperar_senha(GtkWidget *button, gpointer data) {
     g_print("recupera senha");
}