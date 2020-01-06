#include <signal.h>
#include <time.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int signo;
    timer_t timerid;
    struct sigevent sigev;
    struct itimerspec val;
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigaddset(&set, SIGINT);
    if (sigprocmask(SIG_BLOCK, &set, NULL) < 0) {
        perror("sigprocmask");
        return 1;
    }

    memset(&sigev, 0, sizeof sigev);
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGALRM;
    sigev.sigev_value.sival_ptr = &timerid;
    if (timer_create(CLOCK_REALTIME, &sigev, &timerid) < 0) {
        perror("timer_create");
        return 1;
    }

    val.it_interval.tv_sec = 1;
    val.it_interval.tv_nsec = 0;
    val.it_value = val.it_interval;
    if (timer_settime(timerid, 0, &val, NULL) < 0) {
        perror("timer_settime");
        return 1;
    }
    if (timer_gettime(timerid, &val) < 0) {
        perror("timer_gettime");
        return 1;
    }
    printf(
        "it_interval = %ld.%09ld\n"
        "it_value = %ld.%09ld\n",
        val.it_interval.tv_sec, val.it_interval.tv_nsec,
        val.it_value.tv_sec, val.it_value.tv_nsec
    );

    while ((signo = sigwaitinfo(&set, NULL)) != SIGINT) {
        if (signo < 0) {
            perror("sigwaitinfo");
            return 1;
        }
        if (signo = SIGALRM) {
            write(1, ".", 1);
        }
    }
    write(1, "\nSIGINT\n", 8);

    if (timer_delete(timerid) < 0) {
        perror("timer_delete");
        return 1;
    }

    return 0;
}