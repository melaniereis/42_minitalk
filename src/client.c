#include "../inc/minitalk.h"

int error_msg(void);
void   send_msg(int pid, char **msg);

int main(int argc, char **argv)
{
    int i;
    if (argc != 3 & error_msg())
        exit(-1);
    i = 0;
    while (argv[1][i])
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
            exit(ft_printf("Error\nPID is not a number!\n"));
        i++;
    }
    send_msg(ft_atoi(argv[1]), argv[2]);
	return (0);
}

int error_msg(void)
{
    ft_printf("There is an error!\n");
    ft_printf("Verify that the server is launched: ./server\n");
    ft_printf("Then lauch client with the following format:\n");
    ft_printf("./client [server_pid] [string]\n");
    return (1);
}

void   send_msg(int pid, char **msg)
{
    ft_printf("Sending message to %d\n ....\n", pid);
    while (1)
    {

    }
}