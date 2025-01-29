/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:59:37 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/29 21:40:08 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	ft_sighandler(int sig);
static void	ft_send_msg(pid_t pid, char *msg);
static void	ft_send_byte(pid_t pid, unsigned char byte);
static int	ft_init_client(int argc, char **argv);

/**
 * @brief Main function: Initializes the client and sends the message
 * @param argc: Argument count
 * @param argv: Argument vector
 * @return: 0 on success
 */
int	main(int argc, char **argv)
{
	pid_t	server_pid;

	server_pid = ft_init_client(argc, argv);
	ft_printf("%sSending message to Server (PID: %d)%s\n",
		GREEN, server_pid, RESET);
	ft_send_msg(server_pid, argv[2]);
	while (1)
		pause();
	return (0);
}

/**
 * @brief Initializes the client, checks arguments and sets up signal handlers
 * @param argc: Argument count
 * @param argv: Argument vector
 * @return: Server PID
 */
static int	ft_init_client(int argc, char **argv)
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
	sa.sa_handler = ft_sighandler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		ft_printf("%sError: sigaction failed%s\n", RED, RESET);
		exit(EXIT_FAILURE);
	}
	return (server_pid);
}

/**
 * @brief Signal handler for client
 * @param sig: Received signal
 */
static void	ft_sighandler(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("%s* . * . *%s\n", BLUE, RESET);
	else if (sig == SIGUSR2)
	{
		ft_printf("%sMessage sent successfully!%s\n", GREEN, RESET);
		exit(0);
	}
}

/**
 * @brief Sends a message to the server
 * @param pid: Server PID
 * @param msg: Message to send
 */
static void	ft_send_msg(pid_t pid, char *msg)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(msg);
	i = 0;
	ft_send_byte(pid, (unsigned char)(len >> 24));
	ft_send_byte(pid, (unsigned char)(len >> 16));
	ft_send_byte(pid, (unsigned char)(len >> 8));
	ft_send_byte(pid, (unsigned char)len);
	while (i < len)
	{
		ft_send_byte(pid, msg[i]);
		i++;
	}
}

/**
 * @brief Sends a single byte to the server
 * @param pid: Server PID
 * @param byte: Byte to send
 */
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
