#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sigint_handler(int signo)
{
    printf("Caught SIGINT!\n");
    exit(EXIT_SUCCESS);
}

int main(void)
{
    // arg1 ... signal name
    // arg2 ... signal action
    if(signal(SIGINT, sigint_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    for(;;)
        pause();

    return 0;
}

/* Result:
    # ./sigint_sample
    ... Wait until Ctrl + C is pressed ...
    # ^CCaught SIGINT!

*/