/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 18:14:04 by elopukh           #+#    #+#             */
/*   Updated: 2018/04/09 18:14:07 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		isneg(int *n, int *sign)
{
	if (*n < 0)
	{
		*n = -(*n);
		*sign = 1;
	}
}

char			*ft_itoa(int n)
{
	char	*s;
	int		new;
	int		len;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	new = n;
	len = 2;
	sign = 0;
	isneg(&n, &sign);
	while (new /= 10)
		len++;
	len = len + sign;
	if (!(s = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	s[--len] = '\0';
	while (len--)
	{
		s[len] = n % 10 + '0';
		n = n / 10;
	}
	if (sign)
		s[0] = '-';
	return (s);
}
