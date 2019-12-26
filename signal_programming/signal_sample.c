#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

extern const char * const sys_siglist[];

char *strsignal (int signo);

static void signal_handler(int signo)
{
    if (signo == SIGINT)
        printf("Caught %s!\n", strsignal(signo));
    else if (signo == SIGTERM)
        printf("Caught SIGTERM!\n");
    else {
        fprintf(stderr, "Unexpected signal!\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

int main(void)
{
    if(signal(SIGINT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGTERM!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGPROF, SIG_DFL) == SIG_ERR) {
        fprintf(stderr, "Cannot reset SIGPROF!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGHUP, SIG_DFL) == SIG_ERR) {
        fprintf(stderr, "Cannot ignore SIGHUP!\n");
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