/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:39 by damateos          #+#    #+#             */
/*   Updated: 2024/07/07 18:55:14 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

volatile t_message	*g_message = NULL;

/*
S. Server prints pid, set up buffer and wait for messages.
C. Client sends bit until received signal.
S. Server gets message and sets pending flag
	process message:
	1 add bit
	2 if last bit,
		if str end, print, reset state, 
		else, next byte
	3 else next bit
	4 if buff is full, resize
	5 set pending as false
	6 send reveived signal
C. Send next bit on received
 */

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
		ft_printf("1");
		buff->ptr[buff->si] |= (1 << buff->bi);
	}
	else
	{
		ft_printf("0");
		buff->ptr[buff->si] &= ~(1 << buff->bi);
	}
}

int	process_message(t_buffer *buff)
{
	save_bit(buff);
	if (buff->bi == 0)
	{
		ft_printf("\n");
		if (!buff->ptr[buff->si]) // String end
		{
			print_str_and_reset_state(buff);
			if (!buff->ptr)
				return (1);
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
		ft_printf(
			"buffer full, expanding it. Curr len: %s\n",
			ft_itoa((int)buff->len));
		buff->ptr = ft_expand_str(buff->ptr, buff->len, buff->len * 2);
		if (!buff->ptr)
			return (1);
		buff->len *= 2;
		ft_printf("buff new len: %s\n", ft_itoa((int)buff->len));
	}
	return (0);
}

void	send_confirmation(void)
{
	int	sleep_time;

	sleep_time = 300;
	g_message->pending = 0;
	while (!g_message->pending)
	{
		if (kill(g_message->sender, SIGUSR1) == -1)
		{
			ft_printf("Signal sending failed");
		}
		sleep_time = (sleep_time * 2) % 300000;
		usleep(sleep_time);
	}
}

int	main(void)
{
	struct sigaction	sa;
	t_buffer			buff;

	init_str_state(&buff);
	if (!buff.ptr)
		return (1);
	ft_bzero(&sa, sizeof(sa));
	g_message = (t_message *)malloc(sizeof(t_message));
	if (!g_message)
		return (1);
	ft_bzero((void *)g_message, sizeof(t_message));
	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("%s\n", ft_itoa((int)getpid()));
	while (1)
	{
		if (g_message->pending)
		{
			if (process_message(&buff) == 1)
				return (1);
			send_confirmation();
		}
	}
	return (0);
}
