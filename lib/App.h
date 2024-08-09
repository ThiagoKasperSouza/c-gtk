#ifndef APP_H
#define APP_H

#include <stdlib.h>
#include <string.h>
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

void freeInputs(Input *inputs, uint numInputs);
void configInputsCallbacks(Input *inputs, uint numInputs);
void configureInputStyle(Input input);


typedef struct {
    GtkWidget *widget;
    GCallback callback;
    char* css_class;
    GtkWidget  *context;
} Button;

void freeButtons(Button *buttons, uint numButtons);
void configButtonCallbacks(Button *button, uint numInputs);
void configureButtonStyle(Button button);

typedef struct {
    Button *buttons;
    uint numButtons;
    uint numInputs;
    Input *inputs;
} LoginForm;

typedef struct {
    GtkWidget *boxContent;
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
TabMenu* newTabMenu(GtkWidget *window, Tab *tabs, uint numTabs);
void freeTabMenu(TabMenu *mainContainer, uint numTabs);
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
    TabMenu *mainContainer;
    Button *buttons;
}  MainPage;
typedef struct {
    GtkWidget *window;
    GtkWidget *boxContent;
    LoginForm *form;
}  LoginPage;
/*
*
*   END PAGES
*
*/
#endif