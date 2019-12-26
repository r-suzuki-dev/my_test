#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int ret;
    ret = kill(atoi(argv[1]), SIGHUP);
    if (ret)
        perror("kill");

    return 0;
}