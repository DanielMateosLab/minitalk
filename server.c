/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:08:39 by damateos          #+#    #+#             */
/*   Updated: 2024/06/23 22:50:51 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_mt_state
{
	pid_t	sender;
	int		bit;
	int		pending;
}	t_mt_state;

volatile struct s_mt_state state;

void	action(int sig, siginfo_t info, void *context)
{
	// TODO: probably pending flag is not needed, as we will no
	// pass control to client until current signal is processed.
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

int	main()
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&state, 0, siezof(state));
	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	// TODO: block all signals while signal is pending
	/**
	 * While 1,
	 * if bit != -1, save bit. increase buffer if needed. if null pointer, print buffer and restore it.
	 * send confirmation
	 * Wait for signal
	 */
	return (0);
}
