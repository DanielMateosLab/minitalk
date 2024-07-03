/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:39 by damateos          #+#    #+#             */
/*   Updated: 2024/07/03 21:30:09 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
} 	t_buffer;

volatile t_message	*g_message;

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
	buff->bi = 0;
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
	if (g_message->bit)
		buff->ptr[buff->si] |= (1 << buff->bi);
	else
		buff->ptr[buff->si] &= ~(1 << buff->bi);
	if (buff->bi == 7)
	{
		if (!buff->ptr[buff->si])
		{
			print_str_and_reset_state(buff);
			if (!buff->ptr)
				return (1);
		}
		else
		{
			buff->si++;
			buff->bi = 0;
		}
	}
	else
		buff->bi++;
	if (buff->si == buff->len - 1)
	{
		ft_expand_str(&buff->ptr, buff->len, (buff->len *= 2));
		if (!buff->ptr)
			return (1);
	}
	kill(g_message->sender, SIGUSR1);
	return (0);
}

int	main(void)
{
	struct sigaction	sa;
	t_buffer			buff;
	char				*pid;

	init_str_state(&buff);
	if (!buff.ptr)
		return (1);
	ft_memset(&sa, 0, sizeof(sa));
	g_message = (t_message *)malloc(sizeof(t_message));
	if (!g_message)
		return (1);
	ft_memset((void *)g_message, 0, sizeof(t_message));
	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	pid = ft_itoa((int)getpid());
	write(1, pid, ft_strlen(pid));
	ft_putchar_fd('\n', 1);
	while (1)
	{
		if (g_message->pending)
		{
			if (process_message(&buff) == 1)
				return (1);
		}
		pause();
	}
	return (0);
}
