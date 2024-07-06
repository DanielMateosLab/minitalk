/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:07:07 by damateos          #+#    #+#             */
/*   Updated: 2024/01/20 19:36:43 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	includes(char const *set, char c)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	size_t			len;

	start = 0;
	while (s1[start] && includes(set, s1[start]))
		start++;
	len = ft_strlen(s1);
	while (len && includes(set, s1[len - 1]))
		len--;
	return (ft_substr(s1, start, len - start));
}
