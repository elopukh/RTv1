/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:31:06 by elopukh           #+#    #+#             */
/*   Updated: 2018/04/03 20:31:08 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int i;
	int j;
	int a;

	i = 0;
	j = 0;
	if (!*s2)
		return (char*)(s1);
	while (s1[i] != '\0')
	{
		j = 0;
		a = i;
		while (s1[i] == s2[j] && s2[j] != '\0')
		{
			i++;
			j++;
		}
		if (s2[j] == '\0')
			return ((char *)s1 + a);
		else
			i = a;
		i++;
	}
	return (NULL);
}
