#include <gtk/gtk.h>
#include "./TabMenu.h"

struct Tab {
    GtkWidget *boxContent;
    GtkWidget *child;
    GtkWidget *menu_label;
    GtkAlign  v_align;
    GtkAlign  h_align;
};
struct TabMenu {
    GtkWidget *notebook;
    int numTabs;
    struct Tab *tabs;
};

void configTab(GtkWidget *notebook, struct Tab *tab) {    
   // Alinhamento do boxContexnt, vertical e horizontalmente;
   gtk_widget_set_halign(tab->boxContent, tab->h_align);
   gtk_widget_set_valign(tab->boxContent, tab->v_align);
   // Inclui a tab no 'notebook' (menu)
   gtk_notebook_append_page(GTK_NOTEBOOK(notebook), tab->boxContent, tab->menu_label);
   // Faz com que o widget child apareça dentro da tab
   gtk_box_append(GTK_BOX(tab->boxContent), tab->child);
}


TabMenu* newTabMenu(GtkWidget *window, struct Tab *tabs) {
    TabMenu *tm = (TabMenu*) g_slice_alloc(sizeof(struct TabMenu)); 
    
    tm->notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(tm->notebook), GTK_POS_TOP);
    gtk_window_set_child(GTK_WINDOW(window), tm->notebook);

    tm->tabs = tabs;
    tm->numTabs = sizeof(tabs) / sizeof(struct Tab);

    for(int i=0; i <=tm->numTabs+1; i++) {
        configTab(tm->notebook,&tabs[i]);
    }

    return tm;
}

void freeTabMenu(struct TabMenu *mainContainer) {
    gtk_widget_unrealize(mainContainer->notebook);
    
    // Libera a lista de tabs
    for (int i = 0; i < mainContainer->numTabs; i++) {

       gtk_widget_unrealize(mainContainer->tabs[i].boxContent);
       gtk_widget_unrealize(mainContainer->tabs[i].child);
       gtk_widget_unrealize(mainContainer->tabs[i].menu_label);
       gtk_widget_unrealize(mainContainer->tabs[i].h_align);
       gtk_widget_unrealize(mainContainer->tabs[i].v_align);

    }

    g_slice_free1(mainContainer->numTabs * sizeof(struct Tab), mainContainer->tabs);
}