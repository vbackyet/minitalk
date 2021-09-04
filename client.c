#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>



int ft_strlen(char *the_pid)
{
    int i = 0;
    while(the_pid[i] != '\0')
        i++;
    return(i);
}




int ft_atoi_basic(char *the_pid)
{
    int len = ft_strlen(the_pid);
    int n = 0;
    int i = 0;
    while(i < len)
    {
        n = n * 10 + (the_pid[i] - '0');
        i++;
    }
    return(n);
}


// Проверить на валидность аргументы!!!!!!!!!!!!!
int		len(long nb)
{
	int		len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_with_slash(int nb)
{
	char *str;
	long	n;
	int		i;

	n = nb;
	i = len(n) + 1;
	
	if (!(str = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	str[i--] = '\0';

	str[i--] = '/';

	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}






void process_string(char *the_pid, char *the_message)
{
    
    int pid = ft_atoi_basic(the_pid);
    int counter;
	printf("%s", the_message);
    
	int len_counter = 0;
    int len = ft_strlen(the_message);
	int i = 0;
    char ch;
    while (i < len)
    {
        counter = 1<<7;
        ch = the_message[i];
        // if (i==len)
        //     ch = '\n';
        // else
            ch = the_message[i];
        while(counter)
        {

            if (ch & counter)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            counter = counter>>1;
            usleep(100);
        }
        i++;
    }
    exit(1);

}




char *before_slash(char *my_word)
{
	int len = ft_strlen(my_word);
	return (ft_itoa_with_slash(len));
}



char *after_slash(char *my_word, int i)
{
	int len = ft_strlen(my_word);
	len = len - i;
	char *new = (char*)malloc(len + 1);
	int b = 0;
	while(my_word[i])
	{
		new[b] = my_word[i];
		i++;
		b++;
	}
	return (new);
}



int main(int argc, char **argv)
{
    if (!(argc = 3))
        {
            write(1, "wrong number of arguments!\n", 27);
            exit(1);
        }
    else
	{
		char *my_length = before_slash(argv[2]);
		printf("[%s]\n", my_length);
		process_string(argv[1],my_length);		
        process_string(argv[1], argv[2]);
		free(my_length);
	}
    return(0);
}