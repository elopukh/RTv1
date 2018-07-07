/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 16:12:06 by elopukh           #+#    #+#             */
/*   Updated: 2018/02/20 18:34:59 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_push_back(t_list **begin_list, void *content)
{
	t_list *node;

	node = *begin_list;
	if (!node)
	{
		node = ft_create_elem(content);
	}
	else
	{
		while ((node)->next)
		{
			node = node->next;
		}
		node->next = ft_create_elem(content);
	}
}
