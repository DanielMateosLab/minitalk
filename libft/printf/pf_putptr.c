/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:12:58 by damateos          #+#    #+#             */
/*   Updated: 2024/05/17 17:22:29 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putptr(void *ptr)
{
	uintptr_t	address;
	int			count;
	int			temp;

	count = 0;
	address = (uintptr_t)ptr;
	count += pf_putstr("0x");
	if (count < 0)
		return (-1);
	temp = pf_puthex(address, 0);
	if (temp < 0)
		return (-1);
	count += temp;
	return (count);
}
