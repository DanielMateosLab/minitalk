/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: default <default@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:05:27 by default           #+#    #+#             */
/*   Updated: 2024/01/23 23:16:39 by default          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;

	if (!lst || !*lst)
		return ;
	node = *lst;
	if (node->next)
		ft_lstclear(&(node->next), del);
	del(node->content);
	free(node);
	*lst = NULL;
}
