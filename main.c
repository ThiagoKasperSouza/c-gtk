#include <gtk/gtk.h>
#include "./app/App.c"


int main() {
    App *t;
    t = newApp();
 
    return run(t->app, t->status);
}