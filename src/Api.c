#include <gtk/gtk.h>
#include "Api.h"
#include "MainPage.c"


static void print_hello(GtkWidget *widget, gpointer data) {

    g_print("hello world\n");

}


/* ================================================
*
*       PÁGINA DE LOGIN
*
*/


/* Darius Kucinskas - https://stackoverflow.com/questions/5401327/finding-children-of-a-gtkwidget */
// GtkWidget* _find_child(GtkWidget* parent, const gchar* name) {
//     if (g_strcasecmp(gtk_widget_get_name((GtkWidget*)parent), (gchar*)name) == 0) { 
//         return parent;
//     }

//     if (GTK_IS_WIDGET(parent) && gtk_widget_is_instance(parent, GTK_TYPE_BIN)) {
//         GtkWidget *child = gtk_bin_get_child(GTK_BIN(parent));
//         return find_child(child, name);
//     }

//     if (GTK_IS_WIDGET(parent) && gtk_widget_is_instance(parent, GTK_TYPE_CONTAINER)) {
//         GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
//         while ((children = g_list_next(children)) != NULL) {
//             GtkWidget* widget = find_child(children->data, name);
//             if (widget != NULL) {
//                 return widget;
//             }
//         }
//     }

//     return NULL;
// }


void checar_login(GtkWidget *button, gpointer data) {
    GtkWidget *w = (GtkWidget*) data;
    const char* pwd = "minhasenha";

    GtkApplication *app = gtk_window_get_application(GTK_WINDOW(w));
    // GtkWidget *box_content = _find_child(w, "login_box_content");
    // GtkWidget *email_entry = _find_child(box_content, "email_entry");
    // GtkWidget *password_entry = _find_child(box_content, "password_entry");

    // if (email_entry && password_entry) {
    //     const gchar* email = gtk_entry_get_text(GTK_ENTRY(email_entry));
    //     const gchar* password = gtk_entry_get_text(GTK_ENTRY(password_entry));
    // }
    // unsigned char* buf[KEY_SIZE];
    // unsigned char salt[SALT_SIZE];
    
    // scrypt_gensalt(password, salt);


   // _verify_password(password, salt, buf);

    

    gtk_window_close(GTK_WINDOW(w));
    runMainPage(app, data);
}

void abrir_cadastro(GtkWidget *button, gpointer data) {
    GtkWidget* w = (GtkWidget*) data;
    GtkApplication *app = gtk_window_get_application(GTK_WINDOW(w));
    gtk_window_close(GTK_WINDOW(w));
    runMainPage(app, data);
}

void abrir_recuperar_senha(GtkWidget *button, gpointer data) {
    GtkWidget* w = (GtkWidget*) data;
    GtkApplication *app = gtk_window_get_application(GTK_WINDOW(w));
    gtk_window_close(GTK_WINDOW(w));
    runMainPage(app, data);
}
/*
*
*       PÁGINA DE LOGIN
*
* ================================================
*/ 
