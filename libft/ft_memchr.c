/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:09:01 by damateos          #+#    #+#             */
/*   Updated: 2024/01/18 22:18:55 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	to_search;
	size_t			i;

	str = (unsigned char *)s;
	to_search = (unsigned char)c;
	i = 0;
	while (str[i] != to_search && i + 1 < n)
		i++;
	if (i < n && str[i] == to_search)
		return ((void *)&str[i]);
	return (0);
}
