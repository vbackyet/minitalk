#include "minitalk.h"

char *my_letter;
// struct sigaction {
//     void     (*sa_handler)(int);
//     void     (*sa_sigaction)(int, siginfo_t *, void *);
//     sigset_t sa_mask;
//     int      sa_flags;
//     void     (*sa_restorer)(void);
// };




static int	ft_isspace(char c)
{
	if (c == '\t' || c == ' ' || c == '\n' || c == '\v' || c == '\f' ||
			c == '\r')
		return (1);
	return (0);
}

static int	ft_isdigit(char c)
{
	if ((c >= '0' && c <= '9') ||
			(c >= 'A' && c <= 'F'))
		return (1);
	return (0);
}

static char	ft_toupper(char c)
{
	if (c >= 'a' && c <= 'f')
		return (c - 32);
	return (c);
}



int			ft_atoi_base(char *str, int str_base)
{
	int		i;
	int		neg;
	int		ret;

	neg = 1;
	ret = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(ft_toupper(str[i])))
			return (-1);
		ret *= str_base;
		ret += (str[i] <= '9') ? str[i] - '0' : ft_toupper(str[i]) - 55;
		i++;
	}
	return (ret * neg);
}

// static int	spid;
// if (!spid && siginfo->si_pid)
// 	spid = siginfo->si_pid;
// if (spid && spid == siginfo->si_pid)
// 	... handler_body ...

// void	ft_handle(int sig, siginfo_t *siginfo, void *code)
int parse_letter(int dig, int sig, siginfo_t *siginfo, void *code)
{

		(void)sig;
	(void)siginfo;
	(void)code;
	int the_l;
	// init = 0;
	// p =0;

	// static int	spid;
	// write(1, "asd", 3);

// 	if (!spid && siginfo->si_pid)
// 		spid = siginfo->si_pid;
// 	printf( "(%d %d) \n",spid, sig);
// 	if (spid && spid == siginfo->si_pid)
// {

	static int i = 0;
	static int flag = -1;
	static int init = 0;
	static int p = 0;
	static char *my_word = NULL;

	
	if (!my_letter)
		my_letter = (char*)malloc(9);
	my_letter[i] = dig + '0';
	
	i++;
	printf("{%s} - %d\n", my_letter, i);
	if (i == 8)
	{
		my_letter[8] = '\0';
		the_l = ft_atoi_base(my_letter, 2);
		printf("(%c %d)\n", the_l, flag);
		//!!!!!!!!!!!!!!!!
		if (flag == -1)
		{
			if (the_l != '/')
			{
				init = 10*init + (the_l - '0');
			}
			else
				flag = 1;
			if (flag == 1)
			{
			printf("[%d]\n", init);
			my_word = (char*)malloc(init + 1);
			flag = 2;
			}
			// printf("%d\n" , flag);
		}		
		else
		{
			// write(1, &the_l, 1);
			// printf("[%d %d %c %d]\n" , p, init, the_l, flag);
			if (p<init)
			{
				my_word[p] = the_l;
				// printf("||%s||\n", my_word);
				p++;
			}
			if (p==init)
			{
				my_word[p] = '\0';
				printf("|%s|\n", my_word);
				free(my_word);
				flag = -1;
				init = 0;
				p = 0;
				my_word = NULL;
			}
			
		}
		i = 0;
		free(my_letter);

		my_letter = NULL;
	}
// }
	return(0);

}



void acting_function_zero(int sig, siginfo_t *siginfo, void *code)
{
	// printf("1\n");
	// (void)sig;
	// (void)siginfo;
	// (void)code;
	
	parse_letter(1, sig, siginfo, code);
	// usleep(1500);
	
}


void acting_function_one(int sig, siginfo_t *siginfo, void *code)
{
	// printf("0\n");
	// printf("PID - %d\n", siginfo->si_pid);
	// (void)sig;
	// (void)siginfo;
	// (void)code;
	parse_letter(0, sig, siginfo, code);
		// usleep(1500);
	
}


// поменять printf на свой
// сделать бонусы
// отправлять сигналы
// unicode
// сделать норму



int main()
{
	// int sigaction(int signum, const struct sigaction *act,
// struct sigaction *oldact);
	// struct sigation;
	printf("PID %d\n", getpid());
	struct sigaction act_zero = {0};
	struct sigaction act_one = {0};
	act_zero.sa_flags = SA_SIGINFO;
	act_one.sa_flags = SA_SIGINFO;
// struct sigaction act;
//     act.sa_sigaction=&ft_handle;
//     act.sa_flags=SA_SIGINFO;
//     sigaction(SIGUSR2, &act, NULL);
//     sigaction(SIGUSR1, &act, NULL);
//     while (1)
//         pause();
	sigemptyset(&act_zero.sa_mask);
	sigaddset(&act_zero.sa_mask, SIGUSR1);


	sigemptyset(&act_one.sa_mask);
	sigaddset(&act_one.sa_mask, SIGUSR2);
	// act_zero.sa_handler = acting_function_zero;
	// act_one.sa_handler = acting_function_one;
	act_zero.sa_sigaction = &acting_function_zero;
	act_one.sa_sigaction = &acting_function_one;




	sigaction(SIGUSR1, &act_zero, NULL);
	sigaction(SIGUSR2, &act_one, NULL);
	while(1)
		{
			usleep(500);
        // pause();
		}


	// const struct sigaction act; 
	// act.sa_handler = acting_function;
	// printf("%d {%s}", argv, argc[1]);
	// sigaction(SIGUSR1, &act, NULL);
	// sigaction(SIGUSR2, &act, NULL);
	return(0);
}