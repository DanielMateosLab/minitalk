/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:51 by damateos          #+#    #+#             */
/*   Updated: 2024/07/10 20:57:01 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_expand_str(char *str, size_t len, size_t new_len)
{
	char	*temp;
	size_t	i;

	temp = ft_calloc(new_len, sizeof(char));
	if (!temp)
		return (ft_free((void **)str));
	i = 0;
	while (i < len)
	{
		temp[i] = str[i];
		i++;
	}
	ft_free((void **)&str);
	return (temp);
}
