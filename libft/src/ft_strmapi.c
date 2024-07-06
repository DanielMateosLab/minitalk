/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:37:31 by damateos          #+#    #+#             */
/*   Updated: 2024/01/21 19:13:00 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	size;
	size_t	i;
	char	*res;

	size = ft_strlen(s);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	res[size] = '\0';
	i = 0;
	while (i < size)
	{
		res[i] = f((unsigned int)i, s[i]);
		i++;
	}
	return (res);
}
