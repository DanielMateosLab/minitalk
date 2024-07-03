/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:43 by damateos          #+#    #+#             */
/*   Updated: 2024/07/03 23:06:52 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	g_received = 1;

void	handler(int signal)
{
	g_received = 1;
}

int	main(int argc, char	**argv)
{
	struct sigaction	sa;
	size_t				si;
	size_t				bi;
	size_t				len;

	if (argc != 3)
		return (1);
	si = 0;
	bi = 0;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, signal, NULL);
	len = ft_strlen(argv[2]);
	while (si <= len)
	{
		if (g_received)
		{
			if ((argv[2][si] >> bi) & 1)
				kill(argv[1], SIGUSR2);
			else
				kill(argv[1], SIGUSR1);
			if (++bi == 8)
			{
				bi = 0;
				si++;
			}
			pause();
			// TODO: revise and test
		}
	}
	return (0);
}
