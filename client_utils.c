/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:44 by damateos          #+#    #+#             */
/*   Updated: 2024/07/10 20:42:04 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	bit_to_signal(size_t si, size_t bi, char *str)
{
	if (str[si] >> bi & 1)
		return (SIGUSR2);
	else
		return (SIGUSR1);
}
