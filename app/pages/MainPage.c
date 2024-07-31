#include <gtk/gtk.h>
#include "./Defaults.h"
#include "../components/TabMenu/TabMenu.c"


struct MainPage {
    GtkWidget *window;
    struct TabMenu *mainContainer;
    struct Button *buttons;
    int numButtons;
};

void _addButton(struct MainPage *mp, gchar* name, GCallback callback, gpointer data) {

    mp->buttons = realloc(mp->buttons, (mp->numButtons +1) * sizeof(struct Button));

    if (!mp->buttons) {
        // Tratar erro de alocação de memória
        printf("Erro ao alocar memória botão\n");
        return;

    }
        
    /* 
     * mp->buttons age como uma lista de structs
     * logo, atrela a lista de botoes uma nova struct botao
   */
    mp->buttons[mp->numButtons].widget = gtk_button_new_with_label(name);
    mp->buttons[mp->numButtons].name = name;
    mp->buttons[mp->numButtons].callback = callback;
    mp->numButtons++;
    g_signal_connect(mp->buttons[mp->numButtons-1].widget, "clicked", callback, data);
}

static void runMainPage(GtkApplication *app, gpointer user_data) {
    MainPage *mp = g_slice_alloc(sizeof(MainPage));
    
    mp->window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(mp->window), MAIN_PAGE_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(mp->window), WINDOW_WIDTH, WINDOW_HEIGHT);

    mp->buttons = NULL;
    mp->numButtons = 0;
    _addButton(mp, "Hello World 1", G_CALLBACK(print_hello), NULL);
    _addButton(mp, "Hello World 2", G_CALLBACK(print_hello2), NULL);

   mp->mainContainer = newTabMenu(mp->window, (Tab[]) {
        {
        .boxContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0),
        .menu_label = gtk_label_new("Tab1"),
        .child = mp->buttons[0].widget,
        .v_align = GTK_ALIGN_START,
        .h_align = GTK_ALIGN_START,

        },

        {

        .boxContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0),
        .menu_label = gtk_label_new("Tab2"),
        .child = mp->buttons[1].widget,
        .v_align = GTK_ALIGN_START,
        .h_align = GTK_ALIGN_START,

        },

    });

    gtk_window_present(GTK_WINDOW(mp->window));

}
