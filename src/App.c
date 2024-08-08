#include <gtk/gtk.h>
#include "App.h"
#include "Api.c"
#include "LoginPage.c"

/* Motivo de precisar de cast em allocs (void pointers):
* https://www.youtube.com/watch?v=t7CUti_7d7c
*/
int newApp() {

   AppEngine* a = (AppEngine*) g_slice_alloc(sizeof(AppEngine));
   a->appInstance = gtk_application_new(APP_NAME, 0); 
    
   g_signal_connect(a->appInstance,"activate", G_CALLBACK(runLoginPage),NULL);

   a->status = g_application_run(G_APPLICATION(a->appInstance),0,0);
   
   g_slice_free(AppEngine, a);
   return a->status;
}

/*
*
*  TAB_MENU
*
*/
void configTab(GtkWidget *notebook, Tab *tab) {    
   // Alinhamento do boxContexnt, vertical e horizontalmente;
   gtk_widget_set_halign(tab->boxContent, tab->h_align);
   gtk_widget_set_valign(tab->boxContent, tab->v_align);
   // Inclui a tab no 'notebook' (menu)
   gtk_notebook_append_page(GTK_NOTEBOOK(notebook), tab->boxContent, tab->menu_label);
   // Faz com que o widget child apareça dentro da tab
   gtk_box_append(GTK_BOX(tab->boxContent), tab->child);
}


TabMenu* newTabMenu(GtkWidget *window, Tab *tabs) {
    TabMenu *tm = (TabMenu*) g_slice_alloc(sizeof(TabMenu)); 
    
    tm->notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(tm->notebook), GTK_POS_TOP);
    gtk_window_set_child(GTK_WINDOW(window), tm->notebook);

    tm->tabs = tabs;

    for(uint i=0; i < tm->numTabs; i++) {
        configTab(tm->notebook,&tabs[i]);
    }

    return tm;
}

void freeTabMenu(TabMenu *mainContainer, uint numTabs) {
    gtk_widget_unrealize(mainContainer->notebook);
    
    // Libera a lista de tabs
    for (uint i = 0; i < mainContainer->numTabs; i++) {

       gtk_widget_unrealize(mainContainer->tabs[i].boxContent);
       gtk_widget_unrealize(mainContainer->tabs[i].child);
       gtk_widget_unrealize(mainContainer->tabs[i].menu_label);

    }

    g_slice_free1(mainContainer->numTabs * sizeof(Tab), mainContainer->tabs);
}

/*
*
*  END TAB_MENU
*
*/


/*
*
*   INPUTS
*
*/
void configureInputStyle(Input input) {
    GtkCssProvider* provedor_css = gtk_css_provider_new();
    GtkCssProvider* provedor_css_label = gtk_css_provider_new();

    GFile *file = g_file_new_for_path(STYLES_PATH);
    if (!g_file_query_exists(file, NULL)) {
        g_error("Style file not found");
        return;
    }

    gtk_css_provider_load_from_file(provedor_css,file);
    gtk_css_provider_load_from_file(provedor_css_label,file);
    g_object_unref(file);


    gtk_style_context_add_provider(gtk_widget_get_style_context(input.entry), GTK_STYLE_PROVIDER(provedor_css), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_provider(gtk_widget_get_style_context(input.label), GTK_STYLE_PROVIDER(provedor_css_label), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_style_context_add_class(gtk_widget_get_style_context(input.entry), input.css_class);
    gtk_style_context_add_class(gtk_widget_get_style_context(input.label),  g_strdup_printf("%s_label", input.css_class));

    if (!gtk_style_context_has_class(gtk_widget_get_style_context(input.entry), input.css_class)) {
        g_error("Invalid CSS class");
        return;
    }

    g_object_unref(provedor_css);
    g_object_unref(provedor_css_label);
}

void configInputsCallbacks(Input *inputs, uint numInputs) {

    for (uint i = 0; i < numInputs; i++) {
        configureInputStyle(inputs[i]);
    }
    
}

void freeInputs(Input *inputs, uint numInputs) {
    // Libera a lista de botões
    for (uint i = 0; i <  numInputs; i++) {
        gtk_widget_unrealize(inputs[i].entry);
        gtk_widget_unrealize(inputs[i].label);
    }
}
/*
*
*   END INPUTS
*
*/



/* 
*  
*  BUTTONS 
*  
*/
void configureButtonStyle(Button button) {
    GtkCssProvider* provedor_css = gtk_css_provider_new();
    GError* erro = NULL;
    gtk_css_provider_load_from_file(provedor_css, g_file_new_for_path(STYLES_PATH));

    // Verifique se houve um erro ao carregar o CSS
    if (erro != NULL) {
        g_print("Erro ao carregar o CSS: %s\n", erro->message);
        g_error_free(erro);
    }

    gtk_style_context_add_provider(gtk_widget_get_style_context(button.widget), GTK_STYLE_PROVIDER(provedor_css), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(gtk_widget_get_style_context(button.widget), button.css_class);
}

void configButtonCallbacks(Button *buttons, uint numButtons) {

    for (uint i = 0; i <  numButtons; i++) {
        configureButtonStyle(buttons[i]);
        g_signal_connect(buttons[i].widget, "clicked", buttons[i].callback, buttons[i].context);
    }
    
}

void freeButtons(Button *buttons, uint numButtons) {
    // Libera a lista de botões
    for (uint i = 0; i < numButtons; i++) {
        gtk_widget_unrealize(buttons[i].widget);
    }
}
/* 
*  
*  END BUTTONS 
*  
*/