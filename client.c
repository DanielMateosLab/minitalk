/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:43 by damateos          #+#    #+#             */
/*   Updated: 2024/07/11 20:28:23 by damateos         ###   ########.fr       */
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

int	set_up_sigaction(struct sigaction *sa)
{
	sa->sa_handler = handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		return (1);
	return (0);
}

int	send_signal(char *pid, int signal)
{
	g_received = 0;
	if (kill(ft_atoi(pid), signal) == -1)
		return (-1);
	return (0);
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

int	main(int argc, char	**argv)
{
	size_t				len;
	char				*str;
	size_t				bi;
	size_t				si;
	struct sigaction	sa;

	if (argc != 3)
		return (1);
	if (set_up_sigaction(&sa) == 1)
		return (1);
	str = argv[2];
	si = 0;
	bi = 8;
	len = ft_strlen(str);
	while (1)
	{
		if (g_received)
		{
			if (!next_bit(&si, &bi, len))
				return (0);
			if (send_signal(argv[1], bit_to_signal(si, bi, str)) == 1)
				return (1);
		}
	}
	return (0);
}

/*
To test:
 while true; do ./client $PID  "$(cat ~/lorem-ipsum.txt)$(date +%s%3N)";
 sleep 0.1; date +%s%3N; done
*/
