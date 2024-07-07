/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:43 by damateos          #+#    #+#             */
/*   Updated: 2024/07/07 00:13:29 by damateos         ###   ########.fr       */
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
	int					failed;

	if (argc != 3)
		return (1);
	str = argv[2];
	si = 0;
	bi = 8;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	len = ft_strlen(str);
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
			received = 0;
			if (str[si] >> bi & 1)
			{
				ft_printf("1");
				while (!received && !failed)
				{
					failed = kill(ft_atoi(argv[1]), SIGUSR2) == -1;
					if (failed)
					{
						ft_printf("Signal sending failed");
						return (1);
					}
					usleep(300);
				}
			}
			else
			{
				ft_printf("0");
				while (!received && !failed)
				{
					failed = kill(ft_atoi(argv[1]), SIGUSR1) == -1;
					if (failed)
					{
						ft_printf("Signal sending failed");
						return (1);
					}
					usleep(300);
				}
			}
		}
	}
	return (0);
}
