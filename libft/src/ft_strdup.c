/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 23:09:15 by damateos          #+#    #+#             */
/*   Updated: 2024/01/18 20:11:01 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1);
	s2 = (char *)malloc((len + 1) * sizeof(char));
	if (s2 == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	while (len)
	{
		s2[len] = (char)s1[len];
		len--;
	}
	s2[len] = (char)s1[len];
	return (s2);
}
