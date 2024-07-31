#include <gtk/gtk.h>
#include "./Defaults.h"

struct mainContainer {
    GtkWidget *notebook;
    int numTabs;
    struct Tab *tabs;
};
struct MainPage {
    GtkWidget *window;
    struct mainContainer mainContainer;
    struct Button *buttons;
    int numButtons;
};


void _addTab(struct mainContainer *mc,  GtkWidget *child, gchar* label) {

    //redimensiona espaço que vai ser utilizado
    mc->tabs = realloc(mc->tabs, (mc->numTabs + 1) * sizeof(struct Tab));

    if (!mc->tabs) {
        // Tratar erro de alocação de memória
        printf("Erro ao alocar memória tab\n");
        return;
    }

    mc->tabs[mc->numTabs].boxContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    mc->tabs[mc->numTabs].menu_label =  gtk_label_new(label);
    mc->tabs[mc->numTabs].child = child;
    mc->numTabs++;

    gtk_widget_set_halign(mc->tabs[mc->numTabs-1].boxContent, GTK_ALIGN_START);
    gtk_widget_set_valign(mc->tabs[mc->numTabs-1].boxContent, GTK_ALIGN_START);
    gtk_notebook_append_page(GTK_NOTEBOOK(mc->notebook), mc->tabs[mc->numTabs-1].boxContent, mc->tabs[mc->numTabs-1].menu_label);
    gtk_box_append(GTK_BOX(mc->tabs[mc->numTabs-1].boxContent), child);
}

void _addButton(struct MainPage *mp, gchar* name, GCallback callback, gpointer data) {

    mp->buttons = realloc(mp->buttons, (mp->numButtons +1) * sizeof(struct Button));

    if (!mp->buttons) {
        // Tratar erro de alocação de memória
        printf("Erro ao alocar memória botão\n");
        return;

    }

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

    mp->mainContainer.notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(mp->mainContainer.notebook), GTK_POS_TOP);
    gtk_window_set_child(GTK_WINDOW(mp->window), mp->mainContainer.notebook);

    mp->mainContainer.tabs = NULL;
    mp->buttons = NULL;
    mp->numButtons = 0;
    mp->mainContainer.numTabs = 0;


    _addButton(mp, "Hello World 1", G_CALLBACK(print_hello), NULL);
    _addButton(mp, "Hello World 2", G_CALLBACK(print_hello2), NULL);

     _addTab(&mp->mainContainer, mp->buttons[0].widget ,"Tab 1");
     _addTab(&mp->mainContainer, mp->buttons[1].widget, "Tab 2");

    gtk_window_present(GTK_WINDOW(mp->window));

}

void freePage(MainPage *mp) {
    if (mp == NULL) return;
     // Libera window e notebok GTK4
    gtk_widget_unrealize(mp->window);
    gtk_widget_unrealize(mp->mainContainer.notebook);


    // Libera a lista de tabs
    for (int i = 0; i < mp->mainContainer.numTabs; i++) {

       gtk_widget_unrealize(mp->mainContainer.tabs[i].boxContent);
       gtk_widget_unrealize(mp->mainContainer.tabs[i].child);
       gtk_widget_unrealize(mp->mainContainer.tabs[i].menu_label);

    }

    g_slice_free1(mp->mainContainer.numTabs * sizeof(struct Tab), mp->mainContainer.tabs);

     // Libera a lista de botões

    for (int i = 0; i < mp->numButtons; i++) {
        gtk_widget_unrealize(mp->buttons[i].widget);
    }

    g_slice_free1(mp->numButtons * sizeof(struct Button), mp->buttons);
    // Libera a estrutura MainPage

    g_slice_free(MainPage, mp);
}
