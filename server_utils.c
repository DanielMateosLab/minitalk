/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:20:00 by damateos          #+#    #+#             */
/*   Updated: 2024/07/09 22:19:50 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	init_str_state(t_buffer *buff)
{
	buff->len = 3;
	buff->bi = 7;
	buff->si = 0;
	buff->ptr = (char *)ft_calloc(buff->len, sizeof(char));
}

void	print_str_and_reset_state(t_buffer *buff, volatile t_message *g_message)
{
	write(1, buff->ptr, ft_strlen(buff->ptr));
	ft_free((void **)&buff->ptr);
	init_str_state(buff);
	g_message->pending = 0;
}

void	send_confirmation(volatile t_message *g_message)
{
	g_message->pending = 0;
	kill(g_message->sender, SIGUSR1);
}

sigset_t	usr_sigset(void)
{
	sigset_t	set;

	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	return (set);
}
