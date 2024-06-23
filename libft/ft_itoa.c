/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:23:06 by damateos          #+#    #+#             */
/*   Updated: 2024/01/21 18:33:54 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t static	get_size(int n)
{
	size_t	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

void static	handle_min(char *res, int *n, size_t *i)
{
	if (*n == -2147483648)
	{
		res[*i] = '8';
		(*i)--;
		(*n) /= 10;
	}
}

void static	handle_negative(char *res, int *n)
{
	if (*n < 0)
	{
		res[0] = '-';
		(*n) *= -1;
	}
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*res;

	size = get_size(n);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	res[size--] = '\0';
	handle_min(res, &n, &size);
	handle_negative(res, &n);
	if (n == 0)
		res[0] = '0';
	while (n != 0)
	{
		res[size--] = (char)(n % 10 + '0');
		n /= 10;
	}
	return (res);
}
