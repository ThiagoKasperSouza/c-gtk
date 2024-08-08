#include <gtk/gtk.h>
#include "App.h"

static void runLoginPage(GtkApplication *app, gpointer user_data) {
    LoginPage *lp = g_slice_alloc(sizeof(LoginPage));
    
    lp->window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(lp->window), LOGIN_PAGE_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(lp->window), LOGIN_WIDTH, LOGIN_HEIGHT);
    

    lp->boxContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(lp->window), lp->boxContent);

    gtk_widget_set_halign(lp->boxContent , GTK_ALIGN_CENTER);
    gtk_widget_set_valign(lp->boxContent , GTK_ALIGN_START);

    lp->form = g_slice_alloc(sizeof(LoginForm));

    lp->form->inputs = (Input[]) {
        {.label=gtk_label_new("Email:"), .entry=gtk_entry_new(), .css_class="email_input" },
        {.label=gtk_label_new("Senha:"), .entry=gtk_password_entry_new(), .css_class="pwd_input" },
    };

    for(int i=0; i <= LENGTH_OF(lp->form->inputs, Input) +1; i++) {
        gtk_box_append(GTK_BOX(lp->boxContent), lp->form->inputs[i].label);
        gtk_box_append(GTK_BOX(lp->boxContent), lp->form->inputs[i].entry);
    }


    lp->form->buttons = (Button[]) {
        {.widget=gtk_button_new_with_label("Login"), .css_class="bt_login",  .callback=G_CALLBACK(checar_login), .context=lp->window},
        {.widget=gtk_button_new_with_label("Cadastro"), .css_class="bt_register",  .callback=G_CALLBACK(abrir_cadastro), .context=lp->window},
        {.widget=gtk_link_button_new_with_label("","Esqueci a senha"), .css_class="bt_forgot",  .callback=G_CALLBACK(abrir_recuperar_senha), .context=lp->window},
    };
    lp->form->numButtons=3;
    configButtonCallbacks(lp->form->buttons);
    
    for(int i=0; i < lp->form->numButtons; i++) {
        gtk_box_append(GTK_BOX(lp->boxContent), lp->form->buttons[i].widget);
        printf("%d",i);
    }


    gtk_window_present(GTK_WINDOW(lp->window));

}


void freeLoginPage(LoginPage *lp) {
    if (lp == NULL) return;
     // Libera window e notebok GTK4
    gtk_widget_unrealize(lp->window);
    gtk_widget_unrealize(lp->boxContent);

    g_slice_free1(LENGTH_OF(lp->form,LoginForm) * sizeof(LoginForm), lp->form);
    // Libera a estrutura LoginPage
    g_slice_free(LoginPage, lp);
}

