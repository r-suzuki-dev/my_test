#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void func_init()
{
    puts("SIGINT");
}

int main(void)
{
    struct sigaction act;
    sigset_t set, oldset;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);    
    if (sigprocmask(SIG_BLOCK, &set, &oldset) < 0) {
        perror("sigprocmask");
        return 1;
    }
    memset(&act, 0, sizeof act);
    act.sa_handler = func_init;
    if (sigaction(SIGINT, &act, NULL)) {
        perror("sigaction");
        return 1;
    } 

    puts("Calling suspend");
    sigsuspend(&oldset);
    puts("suspend return");

    return 0;
}