#ifndef APP_H
#define APP_H

#include <gtk/gtk.h>
#include "Api.h"

/*
*
*   APP ENGINE
*
*/
#define APP_NAME "com.tks.cgtk"
#define STYLES_PATH "./src/styles.css"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 700

#define LOGIN_WIDTH 300
#define LOGIN_HEIGHT 700

#define MAIN_PAGE_TITLE "C-GTK"
#define MAIN_PAGE_NUM_TABS 2
#define MAIN_PAGE_NUM_BUTTONS 2

#define LOGIN_PAGE_TITLE "Login"
#define LOGIN_PAGE_NUM_INPUTS 2
#define LOGIN_PAGE_NUM_BUTTONS 3


typedef struct {
  GtkApplication *appInstance;
  int status;
} AppEngine;

int newApp();
static void activate(GtkApplication *app, gpointer user_data);
/*
*
*   END APP ENGINE
*
*/


/*
*
*   COMPONENTS
*
*/
typedef struct {
    GtkWidget *label;
    GtkWidget* entry;
    char* css_class;
} Input;

void freeInputs(Input *inputs, uint num_inputs);
void configInputsCallbacks(Input *inputs, uint num_inputs);
void configureInputStyle(Input input);


typedef struct {
    GtkWidget *widget;
    GCallback callback;
    char* css_class;
    GtkWidget  *context;
} Button;

void freeButtons(Button *buttons, uint num_buttons);
void configButtonCallbacks(Button *button, uint num_buttons);
void configureButtonStyle(Button button);

typedef struct {
    Button *buttons;
    uint num_buttons;
    uint num_inputs;
    Input *inputs;
} LoginForm;

typedef struct {
    GtkWidget *box_content;
    GtkWidget *child;
    GtkWidget *menu_label;
    GtkAlign  v_align;
    GtkAlign  h_align;
} Tab;

typedef struct {
    GtkWidget *notebook;
    Tab *tabs;
} TabMenu;

void configTab(GtkWidget *notebook, Tab *tab);
TabMenu* newTabMenu(GtkWidget *window, Tab *tabs, uint num_tabs);
void freeTabMenu(TabMenu *main_container, uint num_tabs);
/*
*
*   END COMPONENTS
*
*/


/*
*
*  PAGES
*
*/
typedef struct {
    GtkWidget *window;
    TabMenu *main_container;
    Button *buttons;
}  MainPage;
typedef struct {
    GtkWidget *window;
    GtkWidget *box_content;
    LoginForm *form;
}  LoginPage;
/*
*
*   END PAGES
*
*/
#endif