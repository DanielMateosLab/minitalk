/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:43 by damateos          #+#    #+#             */
/*   Updated: 2024/07/06 13:49:03 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile t_c_state	*g_state = NULL;

void	handler(int signal)
{
	if (signal != SIGUSR1)
		return;
	g_state->received = 1;
	g_state->bi++;
	if (g_state->bi == 8)
	{
		g_state->bi = 0;
		g_state->si++;
	}
}

int	main(int argc, char	**argv)
{
	struct sigaction	sa;
	size_t				len;

	if (argc != 3)
		return (1);
	g_state = (t_c_state *)malloc(sizeof(g_state));
	g_state->si = 0;
	g_state->bi = -1;
	g_state->received = 1;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	len = ft_strlen(argv[2]);
	while (g_state->si <= len)
	{
		if (g_state->received)
		{
			g_state->received = 0;
			if ((argv[2][g_state->si] >> g_state->bi) & 1)
				kill(ft_atoi(argv[1]), SIGUSR2);
			else
				kill(ft_atoi(argv[1]), SIGUSR1);
			pause();
		}
	}
	free((void *)g_state);
	return (0);
}
