#include <stdio.h>
#include <gtk/gtk.h>
#include "acceuil.h"

static void load_css();

int main(int argc,char **argv){

    gtk_init(&argc, &argv);

    load_css();

    acceuil_init();

    gtk_main();

    return 0;
}







static void load_css(){
    
    GtkCssProvider *cssprovider;
    GdkScreen *screen;
    GdkDisplay *display;

    GFile *css_file=g_file_new_for_path("style.css");

    cssprovider=gtk_css_provider_new();
    display=gdk_display_get_default();
    screen=gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen , GTK_STYLE_PROVIDER(cssprovider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_css_provider_load_from_file(cssprovider,css_file,NULL);
 
}
