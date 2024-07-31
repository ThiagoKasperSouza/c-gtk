#include <gtk/gtk.h>
#include "./Defaults.h"

struct Input {
    gchar* label_name;
    GtkWidget *label;
    GtkWidget* entry;
}

struct Form {
    int num_inputs;
    int num_buttons;
    struct Input *Inputs;
}

struct loginContainer {
    GtkWidget *boxContent;
    struct Input userInput;
    struct Input pwdInput;
    GtkWidget *loginButton;
    GtkWidget *registerButton;
    GtkWidget *forgotButton;

}
struct LoginPage {
    GtkWidget *window;
    struct loginContainer loginContainer;
};


static void runLoginPage(GtkApplication *app, gpointer user_data) {
    LoginPage *lp = g_slice_alloc(sizeof(MainPage));
    
    lp->window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(lp->window), LOGIN_PAGE_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(lp->window), WINDOW_WIDTH, WINDOW_HEIGHT);

    lp->loginContainer.boxContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    lp->loginContainer->userInput.label = gtk_label_new("Nome de usuário:");
    lp->loginContainer->userInput.entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(lp->loginContainer.boxContent), lp->loginContainer->userInput.label);
    gtk_box_append(GTK_BOX(lp->loginContainer.boxContent), lp->loginContainer->userInput.entry);

    lp->loginContainer->pwdInput.label = gtk_label_new("Senha:");
    lp->loginContainer->pwdInput.entry = gtk_entry_new();


    // Botão de login

    GtkWidget* botao_login = gtk_button_new_with_label("Login");

    gtk_box_append(GTK_BOX(lp->loginContainer.boxContent), botao_login);


    // Botão de cadastro
    GtkWidget* botao_cadastro = gtk_button_new_with_label("Cadastre-se");
    gtk_box_append(GTK_BOX(lp->loginContainer.boxContent), botao_cadastro);


    // Botão de recuperação de senha
    GtkWidget* botao_recuperacao = gtk_button_new_with_label("Esqueceu a senha?");
    gtk_box_append(GTK_BOX(lp->loginContainer.boxContent), botao_recuperacao);


    // Conectar sinais para os botões
    g_signal_connect(botao_login, "clicked", G_CALLBACK(checar_login), NULL);
    g_signal_connect(botao_cadastro, "clicked", G_CALLBACK(abrir_janela_cadastro), NULL);
    g_signal_connect(botao_recuperacao, "clicked", G_CALLBACK(abrir_janela_recuperacao), NULL);

    gtk_window_present(GTK_WINDOW(lp->window));

}




void freePage(LoginPage *mp) {
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
