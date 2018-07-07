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


t_vect minus_v(t_vect ot, t_vect chto)
{
	t_vect new;

	new.x = ot.x - chto.x;
	new.y = ot.y - chto.y;
	new.z = ot.z - chto.z;
	return (new);
}

double dot(t_vect a, t_vect b)
{
	int numb;

	numb = a.x * b.x + a.y * b.y + a.z * b.z;
	return (numb);
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

int TraceRay(t_window *win, int t_min, int t_max)
{
	int closest_d = 600000;
    int closest_sphere = 0;
	t_vect t1 = IntersectRaySphere(win);
    if (t1.x >= t_min && t1.x <= t_max && t1.x < closest_d)
    {
		closest_d = t1.x;
		closest_sphere = 1;
	}   
	if (t1.y >= t_min && t1.y <= t_max && t1.y < 600000)
	{
		closest_d = t1.y;
		closest_sphere = 1;
    }
    if (closest_sphere == 0)
		return (0xFFFFFF);
	return (win->Sphere.colour);
}

void CanvasToViewport(t_window *win)
{
	win->D.x = win->x;
	win->D.y = win->y;
	win->D.z = win->dist;
}

void	initdata(t_window *win)
{
	win->size_line = W_WIN;
	win->bpp = 32;
	win->endian = 0;
	win->colour = 265;
	win->dist = 2;
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

void scene1(t_window *win)
{
	win->x = -W_WIN / 2;
	while (win->x < W_WIN / 2)
    {
        win->y = -H_WIN / 2;
        while (win->y < H_WIN / 2)
        {
			CanvasToViewport(win);
			win->colour = TraceRay(win, 1, 600000);
			pixel_put_img(win, win->x + W_WIN/2, win->y + H_WIN/2, win->colour);
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
		win->dist += 10;
		scene1(win);
	}
	if (key == 1)
	{
		win->dist -= 10;
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
	win->Sphere.colour = 0xFF0000;
	win->Sphere.center.x = -100;
	win->Sphere.center.y = 100;
	win->Sphere.center.z = 100;
	win->Sphere.radius = 300;
	win->O.x = 0;
	win->O.y = 0;
	win->O.z = 0;
	init(win);
    scene1(win);
	loop(win);
}