/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:43 by damateos          #+#    #+#             */
/*   Updated: 2024/07/10 20:57:23 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_received = 1;

void	handler(int signal)
{
	if (signal != SIGUSR1)
		return ;
	g_received = 1;
}

int	next_bit(size_t *si, size_t *bi, size_t len)
{
	(*bi)--;
	if (*bi > 7)
	{
		*bi = 7;
		(*si)++;
	}
	if (*si > len)
		return (0);
	return (1);
}

void	set_up_sigaction(struct sigaction *sa)
{
	sa->sa_handler = handler;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGUSR1, sa, NULL);
}

int	send_confirmation(int pid, size_t si, size_t bi, char *str)
{
	g_received = 0;
	while (!g_received)
	{
		if (kill(pid, bit_to_signal(si, bi, str)) == -1)
			return (1);
		usleep(300);
	}
	return (0);
}

int	main(int argc, char	**argv)
{
	struct sigaction	sa;
	size_t				len;
	char				*str;
	size_t				bi;
	size_t				si;

	if (argc != 3)
		return (1);
	str = argv[2];
	si = 0;
	bi = 8;
	set_up_sigaction(&sa);
	len = ft_strlen(str);
	while (1)
	{
		if (g_received)
		{
			if (!next_bit(&si, &bi, len))
				return (0);
			if (send_confirmation(ft_atoi(argv[1]), si, bi, str) == 1)
				return (1);
		}
	}
	return (0);
}
