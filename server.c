/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:39 by damateos          #+#    #+#             */
/*   Updated: 2024/07/10 20:56:56 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

volatile t_message	*g_message = NULL;

void	action(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_message->pending)
		return ;
	g_message->pending = 1;
	g_message->sender = info->si_pid;
	if (sig == SIGUSR1)
		g_message->bit = 0;
	else
		g_message->bit = 1;
	return ;
}

void	init_str_state(struct s_buffer *buff)
{
	buff->len = 3;
	buff->bi = 7;
	buff->si = 0;
	buff->ptr = (char *)ft_calloc(buff->len, sizeof(char));
}

void	print_str_and_reset_state(t_buffer *buff)
{
	write(1, buff->ptr, ft_strlen(buff->ptr));
	ft_free((void **)&buff->ptr);
	init_str_state(buff);
	g_message->pending = 0;
}

void	save_bit(t_buffer *buff)
{
	if (g_message->bit)
	{
		buff->ptr[buff->si] |= (1 << buff->bi);
	}
	else
	{
		buff->ptr[buff->si] &= ~(1 << buff->bi);
	}
}

int	process_message(t_buffer *buff)
{
	save_bit(buff);
	if (buff->bi == 0)
	{
		if (!buff->ptr[buff->si])
		{
			print_str_and_reset_state(buff);
			return (0);
		}
		else
		{
			buff->si++;
			buff->bi = 7;
		}
	}
	else
		buff->bi--;
	if (buff->si == buff->len - 1)
	{
		buff->ptr = ft_expand_str(buff->ptr, buff->len, buff->len * 2);
		buff->len *= 2;
	}
	return (0);
}

void	send_confirmation(void)
{
	g_message->pending = 0;
	while (!g_message->pending)
	{
		kill(g_message->sender, SIGUSR1);
		usleep(600);
	}
}

void	set_up_sa(struct sigaction *sa)
{
	ft_bzero(sa, sizeof(*sa));
	sa->sa_sigaction = action;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
}

int	main(void)
{
	struct sigaction	sa;
	t_buffer			buff;

	init_str_state(&buff);
	if (!buff.ptr)
		return (1);
	g_message = (t_message *)malloc(sizeof(t_message));
	if (!g_message)
		return (1);
	ft_bzero((void *)g_message, sizeof(t_message));
	set_up_sa(&sa);
	ft_printf("%s\n", ft_itoa((int)getpid()));
	while (1)
	{
		if (g_message->pending)
		{
			if (process_message(&buff) == 1)
				return (1);
			if (!buff.ptr)
				return (1);
			send_confirmation();
		}
	}
	return (0);
}
