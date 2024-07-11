/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:39 by damateos          #+#    #+#             */
/*   Updated: 2024/07/11 20:30:36 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

int	set_up_sigaction(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = usr_sigset();
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up signals\n");
		return (1);
	}
	return (0);
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
			print_str_and_reset_state(buff);
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

volatile t_message	*init_g_message(void)
{
	g_message = (t_message *)malloc(sizeof(t_message));
	if (!g_message)
		return (NULL);
	ft_bzero((void *)g_message, sizeof(t_message));
	return (g_message);
}

int	main(void)
{
	t_buffer			buff;
	sigset_t			usr_set;

	usr_set = usr_sigset();
	if (!init_str_state(&buff) || !init_g_message())
		return (1);
	if (set_up_sigaction() == 1)
		return (1);
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
