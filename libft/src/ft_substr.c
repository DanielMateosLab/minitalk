/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 22:25:26 by damateos          #+#    #+#             */
/*   Updated: 2024/01/20 19:37:31 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// dest_len does not include the '\0'
char	*ft_substr(char const *s, unsigned int start, size_t dest_len)
{
	char	*sub;
	size_t	source_len;

	if (s == NULL)
		return (NULL);
	source_len = ft_strlen(s);
	if (start > source_len)
		dest_len = 0;
	else if (dest_len > source_len - start)
		dest_len = source_len - start;
	sub = malloc((dest_len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	if (start > source_len)
		sub[0] = '\0';
	else
		ft_strlcpy(sub, s + start, dest_len + 1);
	return (sub);
}

// edge cases (think that the length of a str is == to the last index):
//	s == NULL
// 	start > source_len
// 	dest_len > source_len - start (max to copy): we limit dest_len