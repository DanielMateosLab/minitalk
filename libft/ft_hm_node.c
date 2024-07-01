/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hm_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:50:09 by damateos          #+#    #+#             */
/*   Updated: 2024/07/01 22:40:48 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hm_node	*ft_hm_node_insert(
	t_hashmap *hm, const char *key, void *value, size_t value_size)
{
	unsigned int	i;
	t_hm_node		*node;

	i = ft_hash(key) % hm->size;
	node = ft_hm_get(hm, key);
	if (node)
		ft_hm_node_remove(hm, key);
	node = (t_hm_node *)malloc(sizeof(t_hm_node));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
		return (ft_free((void **)node));
	node->value = malloc(value_size);
	if (node->value)
		ft_memcpy(node->value, value, value_size);
	node->next = hm->array[i];
	hm->array[i] = node;
	return (node);
}

void	ft_hm_node_remove(t_hashmap *hm, const char *key)
{
	unsigned int	i;
	t_hm_node		*prev;
	t_hm_node		*curr;
	size_t			key_len;

	key_len = ft_strlen(key);
	i = ft_hash(key) % hm->size;
	prev = NULL;
	curr = hm->array[i];
	while (curr && ft_strncmp(key, curr->key, key_len) != 0 && curr->next)
	{
		prev = curr;
		curr = prev->next;
	}
	if (!curr || ft_strncmp(key, curr->key, key_len) != 0)
		return ;
	if (prev)
		prev->next = curr->next;
	else
		hm->array[i] = curr->next;
	ft_free((void **)curr->key);
	ft_free((void **)curr->value);
	ft_free((void **)curr);
}

void	*ft_hm_get(t_hashmap *hm, const char *key)
{
	unsigned int	i;
	size_t			key_len;
	t_hm_node		*node;

	key_len = ft_strlen(key);
	i = ft_hash(key) % hm->size;
	node = hm->array[i];
	while (node && ft_strncmp(key, node->key, key_len) != 0 && node->next)
		node = node->next;
	if (node && ft_strncmp(key, node->key, key_len) == 0)
		return (node->value);
	return (NULL);
}
