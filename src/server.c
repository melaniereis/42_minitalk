/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:59:47 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/25 11:00:36 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static t_server_state	g_state;

static void	ft_signal_handler(int sig, siginfo_t *info, void *context);
static void	ft_process_byte(unsigned char byte, pid_t client_pid);
static void	ft_init_server(void);
static void	ft_handle_message(pid_t client_pid);

int	main(void)
{
	ft_init_server();
	ft_printf("%sServer started. PID: %d%s\n", GREEN, getpid(), RESET);
	while (1)
		pause();
	return (0);
}

static void	ft_init_server(void)
{
	struct sigaction	sa;

	ft_memset(&g_state, 0, sizeof(t_server_state));
	g_state.receiving_len = 1;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = ft_signal_handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		ft_printf("%sError: sigaction() failed%s\n", RED, RESET);
		exit(EXIT_FAILURE);
	}
}

static void	ft_signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	
	g_state.current_byte <<= 1;
	if (sig == SIGUSR2)
		g_state.current_byte |= 1;
	g_state.bit_count++;
	if (g_state.bit_count == 8)
	{
		ft_process_byte(g_state.current_byte, info->si_pid);
		g_state.current_byte = 0;
		g_state.bit_count = 0;
	}
}

static void	ft_process_byte(unsigned char byte, pid_t client_pid)
{
	if (g_state.receiving_len)
	{
		g_state.message_len = byte;
		g_state.receiving_len = 0;
		g_state.message = malloc(g_state.message_len + 1);
		if (!g_state.message)
		{
			ft_printf("%sError: Memory allocation failed%s\n", RED, RESET);
			exit(EXIT_FAILURE);
		}
		ft_printf("%sReceiving message of length: %u%s\n",
			BLUE, (unsigned int)g_state.message_len, RESET);
	}
	else if (g_state.bytes_received < g_state.message_len)
	{
		g_state.message[g_state.bytes_received++] = byte;
		if (g_state.bytes_received == g_state.message_len)
			ft_handle_message(client_pid);
	}
	kill(client_pid, SIGUSR1);
}

static void	ft_handle_message(pid_t client_pid)
{
	g_state.message[g_state.bytes_received] = '\0';
	ft_printf("%sMessage received: %s%s\n", GREEN, g_state.message, RESET);
	free(g_state.message);
	g_state.message = NULL;
	ft_memset(&g_state, 0, sizeof(t_server_state));
	g_state.receiving_len = 1;
	kill(client_pid, SIGUSR2);
}
