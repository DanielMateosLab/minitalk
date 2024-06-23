/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 20:10:55 by damateos          #+#    #+#             */
/*   Updated: 2024/01/21 12:30:04 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_u;
	unsigned char	*src_u;
	size_t			i;

	if ((!dst && !src) || !len || dst == src)
		return (dst);
	if (dst > src)
		return (ft_memcpy(dst, src, len));
	dst_u = (unsigned char *)dst;
	src_u = (unsigned char *)src;
	i = 0;
	while (i < len)
	{
		dst_u[i] = src_u[i];
		i++;
	}
	return (dst);
}
