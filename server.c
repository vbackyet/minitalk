
#include <stdio.h>
#include <signal.h>


// struct sigaction {
//     void     (*sa_handler)(int);
//     void     (*sa_sigaction)(int, siginfo_t *, void *);
//     sigset_t sa_mask;
//     int      sa_flags;
//     void     (*sa_restorer)(void);
// };

int acting_function()
{
	printf("idi n\n");
}


int main( int argv, char **argc)
{
	// int sigaction(int signum, const struct sigaction *act,
// struct sigaction *oldact);
	// struct sigation;
	const struct sigaction act; 
	act.sa_handler = acting_function;
	printf("%d {%s}", argv, argc[1]);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	return(0);
}
