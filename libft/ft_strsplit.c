/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:05:55 by elopukh           #+#    #+#             */
/*   Updated: 2018/04/16 17:24:40 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		countw(char const *s, char c)
{
	int i;
	int num;

	i = 0;
	num = 0;
	if (s[i] != '\0' && s[i] != c)
		num++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			num++;
		i++;
	}
	return (num);
}

static int		count(int *k, int *i, const char *s, char c)
{
	int num;

	num = 0;
	while (s[*k] == c && s[*k] != '\0')
	{
		(*k)++;
		(*i)++;
	}
	while (s[*k] != c && s[*k] != '\0')
	{
		(*k)++;
		num++;
	}
	return (num);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;
	int		num;

	k = 0;
	if (!s || !(str = (char **)malloc(sizeof(s) * (countw(s, c) + 1))))
		return (NULL);
	j = 0;
	while (j < countw(s, c))
	{
		i = k;
		num = count(&k, &i, s, c);
		str[j] = (char *)malloc(sizeof(s) * (num + 1));
		k = i;
		i = 0;
		while (num--)
			str[j][i++] = s[k++];
		str[j++][i] = '\0';
	}
	str[j] = NULL;
	return (str);
}
