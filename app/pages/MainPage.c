#include <gtk/gtk.h>
#include "./Defaults.h"


struct MainPage {
    GtkWidget *window;
    struct TabMenu *mainContainer;
    struct Button *buttons;
};


static void runMainPage(GtkApplication *app, gpointer user_data) {
    MainPage *mp = g_slice_alloc(sizeof(MainPage));
    
    mp->window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(mp->window), MAIN_PAGE_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(mp->window), WINDOW_WIDTH, WINDOW_HEIGHT);



     mp->buttons = (Button[]){
        {.widget=gtk_button_new_with_label("Hello world 1"), .callback=G_CALLBACK(print_hello), .css_class="button_1", .context=mp->window},
        {.widget=gtk_button_new_with_label("Hello world 2"), .callback=G_CALLBACK(print_hello2), .css_class="button_2",.context=mp->window},
    };
    configButtonCallbacks(mp->buttons);

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
