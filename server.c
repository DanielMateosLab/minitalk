/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:39 by damateos          #+#    #+#             */
/*   Updated: 2024/06/26 23:09:06 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// TODO: switch hm_ prefix for ft_
// TODO: test ft_expand_str safe free calls

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

volatile struct s_message	g_message;

void	action(int sig, siginfo_t info, void *context)
{
	if (g_message.pending)
		return ;
	g_message.pending = 1;
	g_message.sender = info.si_pid;
	if (sig == SIGUSR1)
		g_message.bit = 0;
	else
		g_message.bit = 1;
	return ;
}

void	ft_safe_free(void **ptr)
{
	if (!*ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

char	*ft_expand_str(char **str, size_t len, size_t new_len)
{
	char	*temp;
	size_t	i;

	temp = ft_calloc(new_len, sizeof(char));
	if (!temp)
	{
		ft_safe_free(str);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		temp[i] = *str[i];
		i++;
	}
	ft_safe_free(str);
	*str = temp;
}

void	init_str_state(struct s_buffer *buff)
{
	buff->len = 1024;
	buff->bi = 0;
	buff->si = 0;
	buff->ptr = (char *)ft_calloc(buff->len, sizeof(char));
}

void	print_str_and_reset_state(struct s_buffer *buff)
{
	write(1, buff->ptr, ft_strlen(buff->ptr));
	ft_safe_free(&buff->ptr);
	init_str_state(buff);
}

int	main(void)
{
	struct sigaction	sa;
	struct s_buffer		*buff;

	init_str_state(buff);
	if (!buff->ptr)
		return (1);
	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&g_message, 0, siezof(g_message));
	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	while (1)
	{
		if (g_message.pending)
		{
			if (g_message.bit)
				buff->ptr[buff->si] |= (1 << buff->bi);
			else
				buff->ptr[buff->si] &= ~(1 << buff->bi);
			if (buff->bi == 7)
			{
				if (!buff->ptr[buff->si])
				{
					print_str_and_reset_state(&buff);
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
			kill(g_message.sender, SIGUSR1);
		}
		pause();
	}
	return (0);
}
