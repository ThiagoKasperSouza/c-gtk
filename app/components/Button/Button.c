#include "./Button.h"

struct Button {
    GtkWidget *widget;
    GCallback callback;
    char* css_class;
    gpointer context;
};

GtkWidget* configLabel(gchar* label) {
    return gtk_button_new_with_label(label);
}

void configureStyle(struct Button button) {
    GtkCssProvider* provedor_css = gtk_css_provider_new();
    GError* erro = NULL;
    gtk_css_provider_load_from_file(provedor_css, g_file_new_for_path("./app/components/Button/style.css"));

    // Verifique se houve um erro ao carregar o CSS
    if (erro != NULL) {
        g_print("Erro ao carregar o CSS: %s\n", erro->message);
        g_error_free(erro);
    }

    gtk_style_context_add_provider(gtk_widget_get_style_context(button.widget), GTK_STYLE_PROVIDER(provedor_css), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(gtk_widget_get_style_context(button.widget), button.css_class);
}

void configCallbacks(struct Button *buttons) {

    for (int i = 0; i <= LENGTH_OF(buttons,struct Button) +1; i++) {
        configureStyle(buttons[i]);
        g_signal_connect(buttons[i].widget, "clicked", buttons[i].callback, buttons[i].context);
    }
    
}

void freeButtons(struct Button *buttons) {
    // Libera a lista de botões
    for (int i = 0; i <= LENGTH_OF(buttons,struct Button) +1; i++) {
        gtk_widget_unrealize(buttons[i].widget);
    }

    g_slice_free1(LENGTH_OF(buttons,struct Button) * sizeof(struct Button), buttons);
}