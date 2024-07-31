#include <gtk/gtk.h>
#include "./Defaults.h"

struct Input {
    gchar* label_name;
    GtkWidget *label;
    GtkWidget* entry;
};

struct Form {
    int num_inputs;
    struct Button *buttons;
    struct Input *Inputs;
};

struct loginContainer {
    GtkWidget *boxContent;
    struct Input userInput;
    struct Input pwdInput;
    GtkWidget *loginButton;
    GtkWidget *registerButton;
    GtkWidget *forgotButton;

};
struct LoginPage {
    GtkWidget *window;
    struct loginContainer loginContainer;
};


static void runLoginPage(GtkApplication *app, gpointer user_data) {
    LoginPage *lp = g_slice_alloc(sizeof(LoginPage));
    
    lp->window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(lp->window), LOGIN_PAGE_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(lp->window), WINDOW_WIDTH, WINDOW_HEIGHT);
    

    lp->loginContainer.boxContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(lp->window), lp->loginContainer.boxContent);

    lp->loginContainer.userInput.label = gtk_label_new("Nome de usuário:");
    lp->loginContainer.userInput.entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(lp->loginContainer.boxContent), lp->loginContainer.userInput.label);
    gtk_box_append(GTK_BOX(lp->loginContainer.boxContent), lp->loginContainer.userInput.entry);

    lp->loginContainer.pwdInput.label = gtk_label_new("Senha:");
    lp->loginContainer.pwdInput.entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(lp->loginContainer.boxContent), lp->loginContainer.pwdInput.label);
    gtk_box_append(GTK_BOX(lp->loginContainer.boxContent), lp->loginContainer.pwdInput.entry);

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
    g_signal_connect(botao_login, "clicked", G_CALLBACK(checar_login),lp);
    g_signal_connect(botao_cadastro, "clicked", G_CALLBACK(abrir_cadastro),lp);
    g_signal_connect(botao_recuperacao, "clicked", G_CALLBACK(abrir_recuperar_senha),lp);

    gtk_window_present(GTK_WINDOW(lp->window));

}



