#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void signal_handler(int signo)
{
    printf("SIGNAL!\n");
}

int main(void)
{
    struct sigaction act;
    memset(&act, 0, sizeof act);
    act.sa_handler = signal_handler;

    if (sigaction(SIGINT, &act, NULL)) {
        perror("sigaction");
        return 1;
    } 

    sleep(60);
    
    return 0;
}

/* Result:
    # ./sigint_sample
    ... Wait until Ctrl + C is pressed ...
    # ^CCaught SIGINT!

*/