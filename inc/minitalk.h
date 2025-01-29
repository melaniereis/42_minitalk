/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:59:27 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/29 21:48:01 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

/*
** Standard Libraries
*/
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

/*
** Custom Libraries
*/
# include "../libs/libft/includes/libft.h"

/*
** Constants
*/
# define PAUSE 100

/*
** Color Codes for Terminal Output
*/
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

/*
** Structures
*/

/**
 * @brief Server state structure
 * 
 * This structure holds the current state of the server,
 * including the message being received and processing details.
 * 
 * - current_byte: The byte currently being assembled from received bits.
 * - bit_count: The number of bits received for the current byte.
 * - message: The dynamically allocated buffer for the received message.
 * - message_len: The length of the message being received.
 * - bytes_received: The number of bytes received so far.
 * - receiving_len: A flag indicating whether the server is currently 
 * 	 receiving the message length or the message itself.
 * - len_bytes_received: The number of bytes received for the message length.
 */
typedef struct s_server_state
{
	unsigned char	current_byte;
	int				bit_count;
	char			*message;
	size_t			message_len;
	size_t			bytes_received;
	int				receiving_len;
	size_t			len_bytes_received;
}	t_server_state;

#endif
