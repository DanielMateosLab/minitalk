/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:32:50 by damateos          #+#    #+#             */
/*   Updated: 2024/01/20 18:48:11 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_u;
	unsigned char	*src_u;

	if (!dst && !src)
		return (dst);
	dst_u = (unsigned char *)dst;
	src_u = (unsigned char *)src;
	while (n-- > 0)
		dst_u[n] = src_u[n];
	return (dst);
}
