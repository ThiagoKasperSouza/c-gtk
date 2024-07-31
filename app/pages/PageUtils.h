#include "./Defaults.h"
#include "../components/TabMenu/TabMenu.c"
#include "../components/Buttons/Buttons.c"

void freeLoginPage(LoginPage *mp) {
    if (mp == NULL) return;
     // Libera os widgets GTK+
    gtk_widget_unrealize(mp->window);
    gtk_widget_unrealize(mp->loginContainer.notebook);


    // Libera a lista de tabs
    for (int i = 0; i < mp->loginContainer.numTabs; i++) {

       gtk_widget_unrealize(mp->loginContainer.tabs[i].boxContent);
       gtk_widget_unrealize(mp->loginContainer.tabs[i].child);
       gtk_widget_unrealize(mp->loginContainer.tabs[i].menu_label);

    }

    g_slice_free1(mp->mainContainer.numTabs * sizeof(struct Tab), mp->mainContainer.tabs);

    // Libera a estrutura MainPage

    g_slice_free(MainPage, mp);
}

void freeMainPage(MainPage *mp) {
    if (mp == NULL) return;
     // Libera window e notebok GTK4
    gtk_widget_unrealize(mp->window);


    freeTabMenu(mp->mainContainer);

    freeButtons(mp->buttons);
    
    // Libera a estrutura MainPage
    g_slice_free(MainPage, mp);
}