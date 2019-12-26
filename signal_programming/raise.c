#include <signal.h>

void main()
{
    // Kill self
    raise(9);
}