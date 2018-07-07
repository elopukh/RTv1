/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 18:23:25 by elopukh           #+#    #+#             */
/*   Updated: 2018/04/09 18:23:26 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *new;

	new = NULL;
	if (alst && *alst && del)
	{
		while (*alst)
		{
			new = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = new;
		}
		*alst = NULL;
	}
}
