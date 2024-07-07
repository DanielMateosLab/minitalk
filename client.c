/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:43 by damateos          #+#    #+#             */
/*   Updated: 2024/07/07 18:45:26 by damateos         ###   ########.fr       */
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

int	main(int argc, char	**argv)
{
	struct sigaction	sa;
	size_t				len;
	char				*str;
	size_t				bi;
	size_t				si;
	int					signal;
	int					sleep_time;

	if (argc != 3)
		return (1);
	str = argv[2];
	si = 0;
	bi = 8;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	len = ft_strlen(str);
	sleep_time = 1000;
	while (1)
	{
		if (received)
		{
			bi--;
			if (bi > 7)
			{
				bi = 7;
				si++;
				ft_printf("\n");
			}
			if (si > len)
				return (0);
			if (str[si] >> bi & 1)
			{
				ft_printf("1");
				signal = SIGUSR2;
			}
			else
			{
				ft_printf("0");
				signal = SIGUSR1;
			}
			received = 0;
			while (!received)
			{
				if (kill(ft_atoi(argv[1]), signal) == -1)
				{
					ft_printf("Signal sending failed");
					return (1);
				}
				sleep_time = (sleep_time * 2) % 300000;
				usleep(sleep_time);
			}
		}
	}
	return (0);
}
