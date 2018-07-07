/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 18:22:01 by elopukh           #+#    #+#             */
/*   Updated: 2018/04/09 18:22:02 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newl;
	t_list	*tmp;
	t_list	*gol;

	if (!lst || !f)
		return (NULL);
	tmp = f(lst);
	if (!(newl = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	gol = newl;
	lst = lst->next;
	while (lst)
	{
		tmp = f(lst);
		if (!(newl->next = ft_lstnew(tmp->content, tmp->content_size)))
			return (NULL);
		newl = newl->next;
		lst = lst->next;
	}
	return (gol);
}
