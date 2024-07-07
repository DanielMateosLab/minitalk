/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:39 by damateos          #+#    #+#             */
/*   Updated: 2024/07/07 00:13:47 by damateos         ###   ########.fr       */
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

char	*ft_expand_str(char **str, size_t len, size_t new_len)
{
	char	*temp;
	size_t	i;

	temp = ft_calloc(new_len, sizeof(char));
	if (!temp)
	{
		ft_free((void **)str);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		temp[i] = *str[i];
		i++;
	}
	ft_free((void **)str);
	*str = temp;
	return (*str);
}

void	init_str_state(struct s_buffer *buff)
{
	buff->len = 1024;
	buff->bi = 7;
	buff->si = 0;
	buff->ptr = (char *)ft_calloc(buff->len, sizeof(char));
}

void	print_str_and_reset_state(t_buffer *buff)
{
	write(1, buff->ptr, ft_strlen(buff->ptr));
	ft_free((void **)&buff->ptr);
	init_str_state(buff);
}

int	process_message(t_buffer *buff)
{
	int	failed = 0;
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
	if (buff->bi == 0)
	{
		ft_printf("\n");
		if (!buff->ptr[buff->si])
		{
			print_str_and_reset_state(buff);
			if (!buff->ptr)
				return (1);
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
		ft_expand_str(&buff->ptr, buff->len, buff->len * 2);
		if (!buff->ptr)
			return (1);
		buff->len *= 2;
		ft_printf("buff new len: %s\n", ft_itoa((int)buff->len));
	}
	g_message->pending = 0;
	// TODO 1: fix expand str
	while (!g_message->pending && !failed)
	{
		failed = kill(g_message->sender, SIGUSR1) == -1;
		if (failed)
			ft_printf("Signal sending failed");
		usleep(300);
	}
	return (0);
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
		}
	}
	return (0);
}
