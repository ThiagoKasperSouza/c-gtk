#ifndef API_H
#define API_H
#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data);

/* API_LOGIN_PAGE */
void checar_login(GtkWidget *button, gpointer data);
void abrir_cadastro(GtkWidget *button, gpointer data);
void abrir_recuperar_senha(GtkWidget *button, gpointer data);
/* END_API_LOGIN_PAGE */

/* API_MAIN_PAGE */
/* END_API_MAIN_PAGE */
#endif