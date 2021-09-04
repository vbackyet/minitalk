
#include <stdio.h>
#include <unistd.h>
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

	printf("PID is %d\n", getpid());
	
	// const struct sigaction act; 
	// act.sa_handler = acting_function;
	// printf("%d {%s}", argv, argc[1]);
	// sigaction(SIGUSR1, &act, NULL);
	// sigaction(SIGUSR2, &act, NULL);
	return(0);
}





int			main(void)
{
	struct sigaction active_act; //создали две структуры
	struct sigaction null_act;

	active_act.sa_sigaction = activebit;
	null_act.sa_sigaction = nullbit;
	active_act.sa_flags = SA_SIGINFO;
	null_act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &active_act, NULL) != 0)
		error("signal error\n");
	if (sigaction(SIGUSR2, &null_act, NULL) != 0)
		error("signal error\n");
	print_pid();
	ft_bzero(g_to_print.message, BUFFSIZE);
	main_handler();
}

void		activebit(int sig, siginfo_t *info, void *context);


Если в sa_flags указан SA_SIGINFO, то sa_sigaction (вместо sa_handler) задаёт функцию обработки сигнала signum. 
В первом аргументе функция принимает номер сигнала, во втором — указатель на siginfo_t и в третьем — указатель на ucontext_t 
(приведённый к void *) (вообще, функция-обработчик не используется третий аргумент. 
Подробней о ucontext_t смотрите в getcontext(3)).



