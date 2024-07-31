#include <gtk/gtk.h>


#define LENGTH_OF(array,type) (sizeof(array) / sizeof(type))

typedef struct Button Button;

void freeButtons(struct Button *buttons);
void configCallbacks(struct Button *button);
GtkWidget* configLabel(gchar* label);