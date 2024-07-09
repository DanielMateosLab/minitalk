/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 21:43:13 by damateos          #+#    #+#             */
/*   Updated: 2024/07/09 20:35:53 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _GNU_SOURCE

# include "libft/include/libft.h"
# include <unistd.h>
# include <signal.h>

typedef struct s_message
{
	pid_t	sender;
	int		bit;
	int		pending;
}	t_message;

typedef struct s_buffer
{
	char	*ptr;
	int		len;
	int		si;
	int		bi;
}	t_buffer;

typedef struct s_c_state
{
	int		received;
	size_t	si;
	size_t	bi;
}	t_c_state;

void		init_str_state(t_buffer *buff);
void		print_str_and_reset_state(
				t_buffer *buff, volatile t_message *g_message);
void		send_confirmation(volatile t_message *g_message);
sigset_t	usr_sigset(void);

#endif
