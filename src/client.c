/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:59:37 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/25 10:54:49 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void		ft_signal_handler(int sig);
static void		ft_send_message(pid_t pid, char *msg);
static pid_t	ft_init_client(int argc, char **argv);
static void		ft_send_byte(pid_t pid, unsigned char byte);

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	server_pid = ft_init_client(argc, argv);
	ft_printf("%sSending message to Server (PID: %d)%s\n",
		GREEN, server_pid, RESET);
	ft_send_message(server_pid, argv[2]);
	while (1)
		pause();
	return (0);
}

static pid_t	ft_init_client(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				server_pid;

	if (argc != 3)
	{
		ft_printf("%sUsage: ./client [PID] [message]%s\n", RED, RESET);
		exit(EXIT_FAILURE);
	}
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) < 0)
	{
		ft_printf("%sError: PID does not exist%s\n", RED, RESET);
		exit(EXIT_FAILURE);
	}
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ft_signal_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		ft_printf("%sError: sigaction failed%s\n", RED, RESET);
		exit(EXIT_FAILURE);
	}
	return (server_pid);
}

static void	ft_signal_handler(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("%s* . * . *%s\n", BLUE, RESET);
	else if (sig == SIGUSR2)
	{
		ft_printf("%sMessage sent successfully!%s\n", GREEN, RESET);
		exit(0);
	}
}

static void	ft_send_message(pid_t pid, char *msg)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(msg);
	i = 0;
	ft_send_byte(pid, (unsigned char)len);
	usleep(PAUSE * 100);
	while (i < len)
	{
		ft_send_byte(pid, msg[i]);
		usleep(PAUSE * 100);
		i++;
	}
	ft_send_byte(pid, '\0');
}

static void	ft_send_byte(pid_t pid, unsigned char byte)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((byte >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(PAUSE);
		i--;
	}
}
