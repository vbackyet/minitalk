
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

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




int parse_letter(int dig)
{
	static int i = 0;
	int the_l;
	if (!my_letter)
		my_letter = (char*)malloc(9);
	my_letter[i] = dig + '0';
	
	i++;
	// printf("{%s} - %d\n", my_letter, i);
	if (i == 8)
	{
		my_letter[8] = '\0';
		the_l = ft_atoi_base(my_letter, 2);
		write(1, &the_l, 1);
		
		// printf("[%c] - my_letter\n", the_l);
		i = 0;
		free(my_letter);
		my_letter = NULL;
	}

}



void acting_function_zero()
{
	// printf("1\n");
	parse_letter(1);
	
}


void acting_function_one()
{
	// printf("0\n");
	parse_letter(0);
}


// второй сигнал слово
// восемь бит


int main( int argv, char **argc)
{
	// int sigaction(int signum, const struct sigaction *act,
// struct sigaction *oldact);
	// struct sigation;
	printf("PID %d\n", getpid());
	struct sigaction act_zero;
	struct sigaction act_one;
	// act0.sa_flags = SA_SIGINFO;
	// act1.sa_flags = SA_SIGINFO;

	act_zero.sa_handler = acting_function_zero;
	act_one.sa_handler = acting_function_one;
	// act_zero.sa_sigaction = &acting_function_zero;
	// act_one.sa_sigaction = &acting_function_one;
	sigaction(SIGUSR1, &act_zero, 0);
	sigaction(SIGUSR2, &act_one, 0);
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
