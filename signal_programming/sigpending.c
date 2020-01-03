#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);    
    if (sigprocmask(SIG_BLOCK, &set, NULL) < 0) {
        perror("sigprocmask");
        return 1;
    }
    puts("Blocking signal");

    sleep(5);

    if (sigpending(&set) < 0) {
        perror("sigpending");
        return 1;
    }

    if (sigismember(&set, SIGINT))
        puts("SIGINT is pending");
    else
        puts("SIGINT is not pending");

    return 0;
}