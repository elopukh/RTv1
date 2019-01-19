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

typedef struct		Vect
{
	double			x;
	double			y;
	double			z;
}					t_vect;

typedef struct light
{
	char			type;
	t_vect			position;
	double			intensity;
	t_vect			direction;
}					t_light;
typedef struct	s_clos
{
	t_list		*obj;
	int			closd;
}				t_clos;

typedef struct Sphere
{
	int				colour;
	t_vect			center;
	double			radius;
}					t_sphere;
typedef struct Cylinder
{
	int				colour;
	t_vect			center;
	double			radius;
	t_vect			v;
}					t_cyl;
typedef struct Cone
{
	int				colour;
	t_vect			center;
	double			tang;
	t_vect			v;
	int 			minm;
}					t_cone;
typedef struct
{
	t_vect t1;
	int				colourput;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				size_line;
	int				bpp;
	int				endian;
	int				t_min;
	int				t_max;
	char			*img;
	int				x;
	int				y;
	t_vect			D;
	t_vect			p;
	t_vect			norm;
	double			dist;
	t_vect			O;
	t_vect			w;
	//t_light			light;
	t_list			*obj;
	t_list			*light;
	double			closest_d;
	
}					t_window;
t_vect IntersectRaySphere(t_window *win, t_sphere *Sphere);
t_vect IntersectRayCyl(t_window *win, t_cyl *Cyl);
t_vect IntersectRayCone(t_window *win, t_cone *Cone);t_vect mult_v(double chis, t_vect vect);
t_vect plus_v(t_vect vect1, t_vect vect2);
t_vect minus_v(t_vect O, t_vect C);
double vect_len(t_vect vect);
double dot(t_vect a, t_vect b);
#endif
