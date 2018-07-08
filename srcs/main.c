/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 18:43:12 by elopukh           #+#    #+#             */
/*   Updated: 2018/07/06 18:43:13 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	initdata(t_window *win)
{
	win->size_line = W_WIN;
	win->bpp = 32;
	win->endian = 0;
	win->colour = 265;
	win->dist = 100;
	win->img =
	mlx_get_data_addr(win->img_ptr, &win->bpp, &win->size_line, &win->endian);
}


void	init(t_window *win)
{
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, H_WIN, W_WIN, "Window 1!");
	win->img_ptr = mlx_new_image(win->mlx_ptr, H_WIN, W_WIN);
	initdata(win);
}


void	pixel_put_img(t_window *win, int x, int y, int colour)
{
	if (x < H_WIN || y < W_WIN)
	{
		colour = mlx_get_color_value(win->mlx_ptr, colour);
		ft_memcpy(win->img + 4 * W_WIN * y + x * 4, &colour, sizeof(int));
	}
}

double dot(t_vect a, t_vect b)
{
	int numb;

	numb = a.x * b.x + a.y * b.y + a.z * b.z;
	return (numb);
}
t_vect minus_v(t_vect vect1, t_vect vect2)
{
	t_vect new;

	new.x = vect1.x - vect2.x;
	new.y = vect1.y - vect2.y;
	new.z = vect1.z - vect2.z;
	return (new);
}

t_vect mult_v(double chis, t_vect vect)
{
	t_vect new;

	new.x = chis * vect.x;
	new.y = chis * vect.y;
	new.z = chis * vect.z;
	return (new);
}

t_vect plus_v(t_vect vect1, t_vect vect2)
{
	t_vect new;

	new.x = vect1.x + vect2.x;
	new.y = vect1.y + vect2.y;
	new.z = vect1.z + vect2.z;
	return (new);
}

t_vect plus_v_ch(double chis, t_vect vect)
{
	t_vect new;
	
	new.x = vect.x + chis;
	new.y = vect.y + chis;
	new.z = vect.z + chis;
	return (new);
}

double vect_len(t_vect vect)
{
	double len;
	
	len = sqrt(pow(vect.x,2) + pow(vect.y,2));
	return (len);
}

double ComputeLighting(t_vect p,t_vect norm, t_window *win)
{
	double i;
	t_vect l;
	double n_dot_l;

	i = 0;
	if (win->light.type == 'a')
	{
		i += win->light.intensity;
	}
	else 
	{
		if (win->light.type == 'p')
			l = minus_v(win->light.position, p);
		else
			l = win->light.direction;
		n_dot_l = dot(norm, l);
		if (n_dot_l > 0)
			i += win->light.intensity * n_dot_l / (vect_len(norm)*vect_len(l));
	}
	return (i);
}
t_vect IntersectRaySphere(t_window *win)
{
    t_vect C = win->Sphere.center;
    int r = win->Sphere.radius;
	t_vect oc = minus_v(win->O, C);
	t_vect ret;

    double k1 = dot(win->D, win->D);
    double k2 = 2 * dot(oc, win->D);
    double k3 = dot(oc, oc) - r * r;

    double discriminant = k2*k2 - 4*k1*k3;
	if (discriminant < 0)
	{
		ret.x = 600000;
		ret.y = 600000;
		ret.z = 0;
		return (ret);
	}
	ret.x = (-k2 + sqrt(discriminant)) / (2 * k1);
	ret.y = (-k2 - sqrt(discriminant)) / (2 * k1);
	ret.z = 0;
    return (ret);
}


int TraceRay(t_window *win)
{
	int closest_d = 600000;
    int closest_sphere = 0;
	t_vect t1 = IntersectRaySphere(win);
    if (t1.x < closest_d)
    {
		closest_d = t1.x;
		closest_sphere = 1;
	}   
	if (t1.y < closest_d)
	{
		closest_d = t1.y;
		closest_sphere = 1;
    }
	if (closest_sphere == 0)
			return (0xFFFFFF);
	//win->p = plus_v(win->O, mult_v(closest_d, win->D));
	//win->norm = plus_v(win->p, win->Sphere.center);
	//win->norm = mult_v((1 / vect_len(win->norm)),win->norm);
	//int ret_col = 0;
	///ret_col += (win->Sphere.colour & 256) * ComputeLighting(win->p, win->norm, win);
	//ret_col += (int)((win->Sphere.colour >> 8 & 256) * ComputeLighting(win->p, win->norm, win)) << 8;
	//ret_col += (int)((win->Sphere.colour >> 16 & 256) * ComputeLighting(win->p, win->norm, win)) << 16;
	return (win->Sphere.colour);
}

t_vect vect_proisv(t_vect a, t_vect b)
{
	t_vect new;

	new.x = a.y * b.z - a.z * b.y;
	new.y = a.z * b.x - a.x * b.z;
	new.z = a.x * b.y - a.y * b.x;
	return (new);
}

void CanvasToViewport(t_window *win)
{
	t_vect u;
	t_vect v;
	t_vect w_1;
	t_vect vverh;

	vverh.x = 0;
	vverh.y = 1;
	vverh.z = 0;

	u = vect_proisv(win->w, vverh);
	v = vect_proisv(u, win->w);

	u = mult_v(1/vect_len(u), u);
	v = mult_v(1/vect_len(v), v);

	u = mult_v(win->x, u);
	v =  mult_v(win->y, v);
	w_1 = mult_v(win->dist, win->w);

	win->D = plus_v(w_1, plus_v(u, v));
	win->D = mult_v(1/vect_len(win->D), win->D);
}

void scene1(t_window *win)
{
	win->x = -H_WIN/2;
	while (win->x < W_WIN/2)
    {
        win->y = -H_WIN/2;
        while (win->y < H_WIN/2)
        {
			CanvasToViewport(win);
			win->colour = TraceRay(win);
			pixel_put_img(win, win->x + H_WIN/2, win->y + H_WIN/2 , win->colour);
			win->y++;
		}
		win->x++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}

int		key_handler(int key, void *p)
{
	t_window *win;

	win = (t_window*)p;
	if (key == 53)
		exit(1);
	if (key == 0)
	{
		win->O.z += 0.5;
		scene1(win);
	}
	if (key == 1)
	{
		win->O.z -= 0.5;
		scene1(win);
	}
	return (1);
}
void	loop(t_window *win)
{
	mlx_hook(win->win_ptr, 2, 1L << 0, key_handler, win);
	mlx_loop(win->mlx_ptr);
}

int main()
{
    t_window *win;
	win = (t_window*)malloc(sizeof(t_window));
	win->Sphere.colour = 0x00FF00;
	win->Sphere.center.x = 500;
	win->Sphere.center.y = 500;
	win->Sphere.center.z = 0;
	win->Sphere.radius = 300;
	win->light.type = 'd';
	win->w.x = 0;
	win->w.y = 0;
	win->w.z = 1;
	win->light.position.x =	200;
	win->light.position.y = 400;
	win->light.position.z = 550;
	win->light.intensity = 0.6;
	win->light.direction.x = -100;
	win->light.direction.y = 100;
	win->light.direction.z = 0;
	win->O.x = 1;
	win->O.y = 1;
	win->O.z = 1;
	init(win);
    scene1(win);
	loop(win);
}