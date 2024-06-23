/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:05:19 by damateos          #+#    #+#             */
/*   Updated: 2024/01/21 20:58:06 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	ln;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ln = (long)n * -1;
	}
	else
		ln = (long)n;
	if (ln > 9)
		ft_putnbr_fd(ln / 10, fd);
	ft_putchar_fd('0' + ln % 10, fd);
}
