/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:45:09 by elopukh           #+#    #+#             */
/*   Updated: 2018/06/20 13:53:14 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int			newfd(char **new, char **line)
{
	int		i;
	char	*tmp;
	char	*tmp1;

	i = 0;
	if (*new == NULL)
		return (0);
	while ((*new)[i] != '\n' && (*new)[i] != '\0')
		i++;
	if ((*new)[i] == '\0')
		return (0);
	tmp = ft_strsub(*new, 0, i);
	tmp1 = ft_strdup(*line);
	ft_strdel(line);
	*line = ft_strjoin(tmp, tmp1);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
	tmp = ft_strsub((*new), i + 1, (ft_strlen(*new) - i));
	ft_strdel(new);
	*new = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (1);
}

static void	readff(char **new, int fd)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

	tmp = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		tmp = NULL;
		if (!*new)
			*new = ft_strdup(buf);
		else
		{
			tmp = ft_strdup(*new);
			ft_strdel(new);
			*new = ft_strjoin(tmp, buf);
			ft_strdel(&tmp);
		}
		ft_strclr(buf);
	}
}

int			get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	static char		*new[8192];

	tmp = NULL;
	if (fd < 0 || fd > 8192 || (read(fd, buf, 0) < 0))
		return (-1);
	*line = ft_strnew(0);
	if (new[fd] && newfd(&new[fd], line))
		return (1);
	else
	{
		readff(&new[fd], fd);
		if (newfd(&new[fd], line) == 1)
			return (1);
	}
	tmp = ft_strdup(*line);
	ft_strdel(line);
	*line = ft_strjoin(tmp, new[fd]);
	ft_strdel(&tmp);
	ft_strclr(new[fd]);
	if (!*line || ft_strlen(*line) == 0)
		return (0);
	return (1);
}
