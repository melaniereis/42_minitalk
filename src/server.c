/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:59:47 by meferraz          #+#    #+#             */
/*   Updated: 2024/12/27 17:25:58 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static t_server_state	g_state;

static void	ft_sighandler(int sig, siginfo_t *info, void *context);
static void	ft_process_byte(unsigned char byte, pid_t client_pid);
static void	ft_init_server(void);
static void	ft_handle_message(pid_t client_pid);

/**
 * @brief Main function: Initializes the server and waits for signals
 * @return: 0 on success
 */
int	main(void)
{
	ft_init_server();
	ft_printf("%sServer started. PID: %d%s\n", GREEN, getpid(), RESET);
	while (1)
		pause();
	return (0);
}

/**
 * @brief Initializes the server and sets up signal handlers
 */
static void	ft_init_server(void)
{
	struct sigaction	sa;

	ft_memset(&g_state, 0, sizeof(t_server_state));
	g_state.receiving_len = 1;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = ft_sighandler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		ft_printf("%sError: sigaction() failed%s\n", RED, RESET);
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Signal handler for the server
 * @param sig: Received signal
 * @param info: Signal information
 * @param context: Signal context
 */
static void	ft_sighandler(int sig, siginfo_t *info, void *context)
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

/**
 * @brief Processes a received byte
 * @param byte: Received byte
 * @param client_pid: Client's PID
 */
static void	ft_process_byte(unsigned char byte, pid_t client_pid)
{
	if (g_state.receiving_len)
	{
		g_state.message_len = (g_state.message_len << 8) | byte;
		g_state.len_bytes_received++;
		if (g_state.len_bytes_received == 4)
		{
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
	}
	else
	{
		g_state.message[g_state.bytes_received++] = byte;
		if (g_state.bytes_received == g_state.message_len)
			ft_handle_message(client_pid);
	}
	kill(client_pid, SIGUSR1);
}

/**
 * @brief Handles the completed message
 * @param client_pid: Client's PID
 */
static void	ft_handle_message(pid_t client_pid)
{
	g_state.message[g_state.bytes_received] = '\0';
	ft_printf("%sMessage received: %s%s\n", GREEN, g_state.message, RESET);
	free(g_state.message);
	ft_memset(&g_state, 0, sizeof(t_server_state));
	g_state.receiving_len = 1;
	kill(client_pid, SIGUSR2);
}
