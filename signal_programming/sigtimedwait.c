#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int main(void)
{
    sigset_t set;
    struct timespec tv;    

    sigemptyset(&set);
    sigaddset(&set, SIGINT);    
    sigaddset(&set, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &set, NULL) < 0) {
        perror("sigprocmask");
        return 1;
    }
    puts("Blocking signal");

    tv.tv_sec = 5;
    tv.tv_nsec = 0;

    puts("Calling sigtimedwait");
    if (sigtimedwait(&set, NULL, &tv) < 0) {
        if (errno = EAGAIN) {
            puts("time out");
            return 0;
        }
        perror("sigtimedwait");
        return 1;
    }
    puts("nsigtimedwait return");
    return 0;
}