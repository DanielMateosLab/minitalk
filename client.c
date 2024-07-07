/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:43 by damateos          #+#    #+#             */
/*   Updated: 2024/07/07 22:27:40 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	received = 1;

void	handler(int signal)
{
	if (signal != SIGUSR1)
		return ;
	received = 1;
}
void	set_up_sigaction(struct sigaction *sa)
{
	sa->sa_handler = handler;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGUSR1, sa, NULL);
}

int	send_signal(char *pid, int signal)
{
	int					sleep_time;

	sleep_time = 1000;
	received = 0;
	while (!received)
	{
		if (kill(ft_atoi(pid), signal) == -1)
			return (1);
		sleep_time = (sleep_time * 2) % 300000;
		usleep(sleep_time);
	}
	return (0);
}

int	to_next_bit(size_t *si, size_t *bi, size_t len)
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

int	bit_to_signal(size_t si, size_t bi, char *str)
{
	if (str[si] >> bi & 1)
		return (SIGUSR2);
	else
		return (SIGUSR1);
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
	set_up_sigaction(&sa);
	str = argv[2];
	si = 0;
	bi = 8;
	len = ft_strlen(str);
	while (1)
	{
		if (received)
		{
			if (!to_next_bit(&si, &bi, len))
				return (0);
			if (send_signal(argv[1], bit_to_signal(si, bi, str)) == 1)
				return (1);
		}
	}
	return (0);
}

// while true; do ./client 142940 "$(date +%s%3N)"; usleep 10000; date +%s%3N; done