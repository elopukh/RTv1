/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 18:19:35 by elopukh           #+#    #+#             */
/*   Updated: 2018/06/02 18:19:38 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "./minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include "../libft/libft.h"

# define DIST 100
# define H_WIN 1000
# define W_WIN 1000

typedef struct	Vect
{
	double		x;
	double		y;
	double		z;
}				t_vect;

typedef struct Sphere
{
	int			colour;
	t_vect		center;
	int			radius;
	t_sphere	*next;
}				t_sphere;

typedef struct
{
	int			colour;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			size_line;
	int			bpp;
	int			endian;
	int			t_min;
	int			t_max;
	char		*img;
	int			x;
	int			y;
	t_vect		D;
	int			dist;
	t_vect		O;
	t_sphere	Sphere;
}				t_window;

#endif
