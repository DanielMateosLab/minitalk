/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:20:00 by damateos          #+#    #+#             */
/*   Updated: 2024/07/07 20:36:28 by damateos         ###   ########.fr       */
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
	int	sleep_time;

	sleep_time = 1000;
	g_message->pending = 0;
	while (!g_message->pending)
	{
		kill(g_message->sender, SIGUSR1);
		sleep_time = sleep_time * 2;
		usleep(sleep_time);
	}
}
