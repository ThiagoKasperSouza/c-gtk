#ifndef API_H
#define API_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include <stdint.h>
#include "scrypt-kdf.h"

#define ASCII_MIN 33
#define ASCII_MAX 126
#define N 1024
#define R 8
#define P 1
#define KEY_SIZE 32
#define SALT_SIZE 12

char* scrypt_gensalt(uint size);
static void print_hello(GtkWidget *widget, gpointer data);

/* API_LOGIN_PAGE */
void checar_login(GtkWidget *button, gpointer data);
void abrir_cadastro(GtkWidget *button, gpointer data);
void abrir_recuperar_senha(GtkWidget *button, gpointer data);
/* END_API_LOGIN_PAGE */

#endif