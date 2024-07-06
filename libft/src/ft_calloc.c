/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:51:55 by damateos          #+#    #+#             */
/*   Updated: 2024/01/20 17:29:36 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	bytes;

	bytes = count * size;
	ptr = (char *)malloc(bytes);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, bytes);
	return (ptr);
}
