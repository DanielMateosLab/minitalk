/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:43 by damateos          #+#    #+#             */
/*   Updated: 2024/07/06 18:38:45 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	received = 1;

void	handler(int signal)
{
	if (signal != SIGUSR1)
		return ;
	received = 1;
	// g_state->received = 1;
	// g_state->bi = g_state->bi + 1;
	// if (g_state->bi == 8)
	// {
	// 	g_state->bi = 0;
	// 	g_state->si = g_state->si + 1;
	// 	ft_printf("\n");
	// }
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
	bi = 9;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	len = ft_strlen(str);
	while (1)
	{
		if (received)
		{
			bi--;
			if (bi == 0)
			{
				bi = 8;
				si++;
				ft_printf("\n");
			}
			if (si > len)
				return (0);
			received = 0;
			if (str[si] >> bi & 1)
			{
				ft_printf("1");
				kill(ft_atoi(argv[1]), SIGUSR2);
			}
			else
			{
				ft_printf("0");
				kill(ft_atoi(argv[1]), SIGUSR1);
			}
			pause();
		}
	}
	return (0);
}
