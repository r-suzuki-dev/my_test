#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);    
    sigaddset(&set, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &set, NULL) < 0) {
        perror("sigprocmask");
        return 1;
    }
    puts("Blocking signal");

    if (sigwaitinfo(&set, NULL) < 0)
    {
        perror("sigwaitinfo");
        return 1;
    }
    puts("nsigwaitinfo return");

    return 0;
}