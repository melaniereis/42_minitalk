/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:59:27 by meferraz          #+#    #+#             */
/*   Updated: 2024/12/27 17:24:27 by meferraz         ###   ########.fr       */
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
