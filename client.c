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

void process_string(char *the_pid, char *the_message)
{
    
    int pid = ft_atoi_basic(the_pid);
    int counter;
    int i = 0;
    while (the_message[i])
    {
        counter = 1<<7;
        while(counter)
        {

            if (the_message[i] & counter)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            counter = counter>>1;
            printf("%d\n",counter);
            usleep(1000000000000000000000000000000000000000000000000);
        }
        i++;
    }
    exit(1);

}




int main(int argc, char **argv)
{
    if (!(argc = 3))
        {
            write(1, "wrong number of arguments!\n", 27);
            exit(1);
        }
    else
        process_string(argv[1], argv[2]);
    return(0);
}