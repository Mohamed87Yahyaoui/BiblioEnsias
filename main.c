#include <stdio.h>
#include <gtk/gtk.h>
#include "pages/main_page/acceuil.h"


int main(int argc,char **argv){
    GApplication * app;
    gtk_init(&argc, &argv);
    app=g_application_new("test.test",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(acceuil_init),NULL);
    int status=g_application_run(G_APPLICATION(app),argc,argv);
    gtk_main();
    g_object_unref(app);
    return status;
}

