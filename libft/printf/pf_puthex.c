/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:07:03 by damateos          #+#    #+#             */
/*   Updated: 2024/05/17 18:04:29 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_puthex(uintptr_t n, int is_upper)
{
	int		count;
	char	*base;
	int		err;

	count = 0;
	if (is_upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n < 16)
		return (pf_putchar(base[n]));
	else
	{
		count += check_err(pf_puthex(n / 16, is_upper), &err);
		if (err)
			return (-1);
		count += check_err(pf_putchar(base[n % 16]), &err);
		if (err)
			return (-1);
	}
	return (count);
}
