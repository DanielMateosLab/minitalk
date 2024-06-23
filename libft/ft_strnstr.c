/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:46:13 by damateos          #+#    #+#             */
/*   Updated: 2024/01/16 23:38:25 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (len && *haystack && *haystack != *needle)
	{
		haystack++;
		if (len)
			len--;
	}
	while (len && haystack[i] == needle[i] && needle[i])
	{
		i++;
		if (len)
			len--;
	}
	if (!needle[i])
		return ((char *)haystack);
	if (!len || !haystack[i])
		return (0);
	return (ft_strnstr(haystack + 1, needle, len - 1 + i));
}
