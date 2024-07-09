/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:39 by damateos          #+#    #+#             */
/*   Updated: 2024/07/09 21:02:40 by damateos         ###   ########.fr       */
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

void	set_up_sigaction(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = usr_sigset();
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
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

void	process_message(t_buffer *buff)
{
	if (g_message->bit)
		buff->ptr[buff->si] |= (1 << buff->bi);
	else
		buff->ptr[buff->si] &= ~(1 << buff->bi);
	if (buff->bi == 0)
	{
		if (!buff->ptr[buff->si])
		{
			print_str_and_reset_state(buff, g_message);
			return ;
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
}

int	main(void)
{
	t_buffer			buff;
	sigset_t			usr_set;

	usr_set = usr_sigset();
	init_str_state(&buff);
	if (!buff.ptr)
		return (1);
	g_message = (t_message *)malloc(sizeof(t_message));
	if (!g_message)
		return (1);
	ft_bzero((void *)g_message, sizeof(t_message));
	set_up_sigaction();
	ft_printf("%s\n", ft_itoa((int)getpid()));
	while (1)
	{
		if (g_message->pending)
		{
			sigprocmask(SIG_BLOCK, &usr_set, NULL);
			process_message(&buff);
			if (!buff.ptr)
				return (1);
			sigprocmask(SIG_UNBLOCK, &usr_set, NULL);
			send_confirmation(g_message);
		}
	}
	return (0);
}
