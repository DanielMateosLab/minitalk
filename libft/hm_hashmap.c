/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_hashmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:04:00 by damateos          #+#    #+#             */
/*   Updated: 2024/06/09 10:44:55 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Typical max size of unsigned int: 2^32 4.294.967.295 or 4mb
// Algo of my namesake djb2 (Daniel J. Bernstein)

unsigned int	hm_hash(const char *string)
{
	const unsigned char	*u_str;
	unsigned int		hash;

	hash = 5381;
	u_str = (const unsigned char *)string;
	while (*u_str)
		hash = hash * 33 + ft_tolower(*u_str++);
	return (hash);
}

// TODO: Create free utility to set freed value to NULL and return NULL
t_hm_node	*hm_insert(
	t_hm_hashmap *map, const char *key, void *value, size_t value_size)
{
	unsigned int	index;
	t_hm_node		*new_node;

	index = hash(key) % map->size;
	new_node = (t_hm_node *)malloc(sizeof(t_hm_node));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = malloc(value_size);
	if (!new_node->value)
	{
		free(new_node->key);
		free(new_node);
		return (NULL);
	}
	ft_memcpy(new_node->value, value, value_size);
	new_node->next = map->array[index];
	map->array[index] = new_node;
	return (new_node);
}
