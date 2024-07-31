#include "./App.h"
#include "./pages/MainPage.c"
	
struct AppEngine  {
  GtkApplication *appInstance;
  int status;
};

int newApp() {
   AppEngine* a = (AppEngine*) g_slice_alloc(sizeof(AppEngine));
   a->appInstance = gtk_application_new(APP_NAME, 0); 
    
   g_signal_connect(a->appInstance,"activate", G_CALLBACK(runMainPage),NULL);

   a->status = g_application_run(G_APPLICATION(a->appInstance),0,0);
   
   g_slice_free(AppEngine, a);
   return a->status;
}
