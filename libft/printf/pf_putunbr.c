/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:52:27 by damateos          #+#    #+#             */
/*   Updated: 2024/05/17 18:00:54 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putunbr(unsigned int n)
{
	int	count;
	int	err;

	count = 0;
	if (n < 10)
	{
		count += check_err(pf_putchar('0' + n), &err);
		if (err)
			return (-1);
	}
	else
	{
		count += check_err(pf_putunbr(n / 10), &err);
		if (err)
			return (-1);
		count += check_err(pf_putchar('0' + n % 10), &err);
		if (err)
			return (-1);
	}
	return (count);
}
