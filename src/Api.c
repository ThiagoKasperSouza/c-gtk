#include <gtk/gtk.h>
#include "Api.h"
#include "MainPage.c"

static void print_hello(GtkWidget *widget, gpointer data) {

    g_print("hello world\n");

}

/**
*
* gerar salt somente no cadastro 
* no login -> pegar user por email (garantir q seja unico no banco); rodar scrypt com o salt  
*/
void scrypt_gensalt(char* buff) {
    struct timespec ts;
    uint64_t nanos = 0;

    // Obtém o tempo em nanossegundos
    clock_gettime(CLOCK_MONOTONIC, &ts);
    nanos = ts.tv_sec * 1000000000ULL + ts.tv_nsec;

    // Combina o tempo em nanossegundos com outros dados para aumentar a entropia
    // Semente inicial para o CSPRNG
    RAND_seed(&nanos, sizeof(nanos));

    // Gera os bytes aleatórios diretamente no buffer
    if (!RAND_bytes(buff, SALT_SIZE)) {
        perror("RAND_bytes");
        exit(1);
    }

    // Garante que o buffer seja nulo-terminado
    buff[SALT_SIZE] = '\0';
}

/* ================================================
*
*       PÁGINA DE LOGIN
*
*/

/* TODO: logica que implementa garantia de cadastro unico pra cada email */


void fazer_login(GtkWidget *button, gpointer data) {
    FormContext *fc = (FormContext *) data;
    GtkWidget *w = fc->window;
    GtkApplication *app = gtk_window_get_application(GTK_WINDOW(w));
    const gchar* entry_text = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(fc->email_entry)));
    g_print("email entry %s\n", entry_text);



    if (g_strcmp0(entry_text, "teste") == 0) {

        GtkApplication *app = gtk_window_get_application(GTK_WINDOW(w));

        gtk_window_close(GTK_WINDOW(w));
        runMainPage(app, data);
        g_print("Texto da entrada é igual ao valor desejado!\n");
    } else {
        g_print("Texto da entrada é diferente do valor desejado!\n");
    }


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
