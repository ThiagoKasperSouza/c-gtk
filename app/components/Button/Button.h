#include <gtk/gtk.h>


#define LENGTH_OF(array,type) (sizeof(array) / sizeof(type))

typedef struct Button Button;

void freeButtons(struct Button *buttons);
void configButtonCallbacks(struct Button *button);
void configureButtonStyle(struct Button button);