#include <stdio.h>
#include <gtk/gtk.h>
#include "acceuil.h"


int main(int argc,char **argv){

    gtk_init(&argc, &argv);

    acceuil_init();

    gtk_main();

    return 0;
}

