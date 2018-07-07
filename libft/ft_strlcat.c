/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:57:26 by elopukh           #+#    #+#             */
/*   Updated: 2018/04/03 20:58:14 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	const char	*s;
	char		*d;
	size_t		k;
	size_t		length;

	s = src;
	d = dst;
	k = dstsize;
	while (k-- != 0 && *d != '\0')
		d++;
	length = d - dst;
	k = dstsize - length;
	if (k == 0)
		return (length + ft_strlen(s));
	while (*s != '\0')
	{
		if (k != 1)
		{
			*d++ = *s;
			k--;
		}
		s++;
	}
	*d = '\0';
	return (length + (s - src));
}
