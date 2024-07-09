/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:20:00 by damateos          #+#    #+#             */
/*   Updated: 2024/07/09 22:24:44 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*init_str_state(t_buffer *buff)
{
	buff->len = 3;
	buff->bi = 7;
	buff->si = 0;
	buff->ptr = (char *)ft_calloc(buff->len, sizeof(char));
	return (buff->ptr);
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

char	*ft_expand_str(char *str, size_t len, size_t new_len)
{
	char	*temp;
	size_t	i;

	temp = ft_calloc(new_len, sizeof(char));
	if (!temp)
		return (ft_free((void **)str));
	i = 0;
	while (i < len)
	{
		temp[i] = str[i];
		i++;
	}
	ft_free((void **)&str);
	return (temp);
}
