/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 23:34:12 by damateos          #+#    #+#             */
/*   Updated: 2024/01/20 17:24:23 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	len;

	len = 0;
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s2);
	s3 = malloc((len + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	if (s1)
		ft_strlcpy(s3, s1, len + 1);
	if (s2)
		ft_strlcat(s3, s2, len + 1);
	return (s3);
}

// Edge cases:
// - s1, s2 or both are null
