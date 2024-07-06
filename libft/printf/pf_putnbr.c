/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:59:44 by damateos          #+#    #+#             */
/*   Updated: 2024/05/17 17:56:45 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putnbr(int n)
{
	long	ln;
	int		count;
	int		err;

	count = 0;
	err = 0;
	if (n < 0)
	{
		count += check_err(pf_putchar('-'), &err);
		if (err)
			return (-1);
		ln = (long)n * -1;
	}
	else
		ln = (long)n;
	if (ln > 9)
		count += check_err(pf_putnbr(ln / 10), &err);
	if (err)
		return (-1);
	count += check_err(pf_putchar('0' + ln % 10), &err);
	if (err)
		return (-1);
	return (count);
}
