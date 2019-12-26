#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int ret;

    // Check send signal permission to the process
    ret = kill(atoi(argv[1]), 0);
    if (ret)
        puts("we lack permission");
    else
        puts("we have permission");
    
    return 0;
}