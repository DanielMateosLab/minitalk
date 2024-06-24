/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:39 by damateos          #+#    #+#             */
/*   Updated: 2024/06/24 23:28:10 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// TODO: switch hm_ prefix for ft_

typedef struct s_mt_state
{
	pid_t	sender;
	int		bit;
	int		pending;
}	t_mt_state;

volatile struct s_mt_state state;

void	action(int sig, siginfo_t info, void *context)
{
	if (state.pending)
		return ;
	state.pending = 1;
	state.sender = info.si_pid;
	if (sig == SIGUSR1)
		state.bit = 0;
	else
		state.bit = 1;
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
		ft_safe_free(*str);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		temp[i] = *str[i];
		i++;
	}
	ft_safe_free(*str);
	*str = temp;
}

int	main()
{
	struct sigaction	sa;
	char				*str;
	int					str_i;
	int					bit_i;
	int					str_len;

	str_len = 1024;
	str = (char *)ft_calloc(str_len, sizeof(char));
	if (!str)
		return (1);
	str_i = 0;
	bit_i = 0;
	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&state, 0, siezof(state));
	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	while (1)
	{
		if (state.pending)
		{
			if (state.bit)
				str[str_i] |= (1 << bit_i);
			else
				str[str_i] &= ~(1 << bit_i);
			if (++bit_i == 7)
			{
				// if char is \0, print and clear string.
				str_i++;
				bit_i = 0;
			}
			if (str_i == str_len - 1)
			{
				ft_expand_str(&str, str_len, (str_len *= 2));
				if (!str)
					return (1);
			}
			// send confirmation
			// wait for signal
		}
	}
	return (0);
}
