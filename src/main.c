#include "../inc/client.h"

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    init_authorization();
    gtk_main();

    return 0;
}
