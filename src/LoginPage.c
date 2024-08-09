#ifndef LOGIN_PAGE_C
#define LOGIN_PAGE_C

#include <gtk/gtk.h>
#include "App.h"


void freeLoginPage(LoginPage *lp) {
    if(lp == NULL) return;
    if(GTK_IS_WIDGET(lp->window))  gtk_widget_unrealize(lp->window);
    g_print("destroyed window\n");
}

static void runLoginPage() {
    LoginPage *lp = g_slice_alloc(sizeof(LoginPage));
    
    lp->window = gtk_window_new();

    gtk_window_set_title(GTK_WINDOW(lp->window), LOGIN_PAGE_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(lp->window), LOGIN_WIDTH, LOGIN_HEIGHT);
    

    lp->boxContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(lp->window), lp->boxContent);

    gtk_widget_set_halign(lp->boxContent , GTK_ALIGN_CENTER);
    gtk_widget_set_valign(lp->boxContent , GTK_ALIGN_START);

    lp->form = g_slice_alloc(sizeof(LoginForm));
    lp->form->numButtons=LOGIN_PAGE_NUM_BUTTONS;
    lp->form->numInputs=LOGIN_PAGE_NUM_INPUTS;

    lp->form->inputs = (Input[LOGIN_PAGE_NUM_INPUTS]) {
        {.label=gtk_label_new("Email:"), .entry=gtk_entry_new(), .css_class="email_input" },
        {.label=gtk_label_new("Senha:"), .entry=gtk_password_entry_new(), .css_class="pwd_input" },
    };
    configInputsCallbacks(lp->form->inputs,LOGIN_PAGE_NUM_INPUTS);

    for(uint i=0; i < lp->form->numInputs; i++) {
        gtk_box_append(GTK_BOX(lp->boxContent), lp->form->inputs[i].label);
        gtk_box_append(GTK_BOX(lp->boxContent), lp->form->inputs[i].entry);
    }


    lp->form->buttons = (Button[LOGIN_PAGE_NUM_BUTTONS]) {
        {.widget=gtk_button_new_with_label("Login"), .css_class="bt_login",  .callback=G_CALLBACK(checar_login), .context=lp->window},
        {.widget=gtk_button_new_with_label("Cadastro"), .css_class="bt_register",  .callback=G_CALLBACK(abrir_cadastro), .context=lp->window},
        {.widget=gtk_button_new_with_label("Esqueci a senha"), .css_class="bt_forgot",  .callback=G_CALLBACK(abrir_recuperar_senha), .context=lp->window},
    };

    configButtonCallbacks(lp->form->buttons, LOGIN_PAGE_NUM_BUTTONS);
    
    for(uint i=0; i < lp->form->numButtons; i++) {
        gtk_box_append(GTK_BOX(lp->boxContent), lp->form->buttons[i].widget);
    }


    gtk_window_present(GTK_WINDOW(lp->window));
    g_signal_connect(GTK_WINDOW(lp->window), "destroy", G_CALLBACK(freeLoginPage), lp);

}
#endif