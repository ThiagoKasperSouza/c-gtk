#include <gtk/gtk.h>
#include "./MainPage.h"

struct Tab {
    GtkWidget *boxContent;
    GtkWidget *child;
    GtkWidget * menu_label;
};

struct mainContainer {
    GtkWidget *notebook;
    int numTabs;
    struct Tab *tabs;
};

struct MainPage {
    GtkWidget *window;
    struct mainContainer mainContainer;
};

void _addTab(struct mainContainer *mc,  GtkWidget *child, gchar* label) {
    //redimensiona espaço que vai ser utilizado
    struct Tab* tab = realloc(mc->tabs, (mc->numTabs + 1) * sizeof(struct Tab));
    if (!tab) {
        // Tratar erro de alocação de memória
        printf("Erro ao alocar memória\n");
        return;
    }
    tab->boxContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    tab->menu_label =  gtk_label_new(label);
    tab->child = child;
    mc->tabs = tab;
    mc->numTabs++;
    gtk_widget_set_halign(tab->boxContent, GTK_ALIGN_START);
    gtk_widget_set_valign(tab->boxContent, GTK_ALIGN_START);
    gtk_notebook_append_page(GTK_NOTEBOOK(mc->notebook), tab->boxContent, tab->menu_label);
    gtk_box_append(GTK_BOX(tab->boxContent), child);
}


static void activate(GtkApplication *app, gpointer user_data) {
    MainPage *mp = malloc(sizeof(MainPage));
    
    mp->window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(mp->window), TITLE);
    gtk_window_set_default_size(GTK_WINDOW(mp->window), WINDOW_WIDTH, WINDOW_HEIGHT);

    mp->mainContainer.notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(mp->mainContainer.notebook), GTK_POS_TOP);
    gtk_window_set_child(GTK_WINDOW(mp->window), mp->mainContainer.notebook);

    mp->mainContainer.tabs = NULL;
    mp->mainContainer.numTabs = 0;

    GtkWidget *button1 = gtk_button_new_with_label("Hello World 1");
    g_signal_connect(button1, "clicked", G_CALLBACK(print_hello), NULL);
    GtkWidget *button2 = gtk_button_new_with_label("Hello World 2");
    g_signal_connect(button2, "clicked", G_CALLBACK(print_hello2), NULL);

    _addTab(&mp->mainContainer, button1 ,"Tab 1");
    _addTab(&mp->mainContainer, button2, "Tab 2");

    gtk_window_present(GTK_WINDOW(mp->window));

}

void freePage(MainPage *mp) {
    if (mp == NULL) return;
     // Libera os widgets GTK+
    gtk_widget_unrealize(mp->window);
    gtk_widget_unrealize(mp->mainContainer.notebook);


    // Libera a lista de tabs
    for (int i = 0; i < mp->mainContainer.numTabs; i++) {

       gtk_widget_unrealize(mp->mainContainer.tabs[i].boxContent);
       gtk_widget_unrealize(mp->mainContainer.tabs[i].child);
       gtk_widget_unrealize(mp->mainContainer.tabs[i].menu_label);

    }

    free(mp->mainContainer.tabs);

    // Libera a estrutura MainPage
    free(mp);
}