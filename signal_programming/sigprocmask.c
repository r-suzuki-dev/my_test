#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
    sigset_t set, oldset;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);    
    if (sigprocmask(SIG_BLOCK, &set, &oldset) < 0) {
        perror("sigprocmask");
        return 1;
    }
    puts("Block SIGINT");

    sleep(5);

    puts("non block SIGINT");
    if (sigprocmask(SIG_SETMASK, &oldset, NULL) < 0) {
        perror("sigprocmask");
        return 1;
    }
    sleep(5);
    return 0;
}