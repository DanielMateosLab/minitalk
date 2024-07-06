/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:24:05 by damateos          #+#    #+#             */
/*   Updated: 2023/12/17 18:39:50 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Si el destize es mayor o igual que src len + 1, copiamos src 
// entera (con su null terminator) en dst.
// Si no, copiamos dstsize - 1 bytes de src en dst y le ponemos
// un null terminator al final
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize >= src_len + 1)
		ft_memcpy(dst, src, src_len + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (src_len);
}
