/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:14:55 by elopukh           #+#    #+#             */
/*   Updated: 2018/04/03 20:14:58 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char		*b2;

	if (!b && len == 0)
		return (NULL);
	b2 = b;
	while (len--)
		*b2++ = (unsigned char)c;
	return (b);
}
