/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:36:42 by damateos          #+#    #+#             */
/*   Updated: 2024/01/16 22:45:08 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = ((unsigned char *)s1);
	p2 = ((unsigned char *)s2);
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		else
		{
			p1++;
			p2++;
		}
	}
	return (0);
}
