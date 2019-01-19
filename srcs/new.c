/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:52:11 by elopukh           #+#    #+#             */
/*   Updated: 2018/09/13 14:52:12 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	pixel_put_img(t_window *win, int x, int y, int colour)
{
	if (x < H_WIN || y < W_WIN)
	{
		colour = mlx_get_color_value(win->mlx_ptr, colour);
		ft_memcpy(win->img + 4 * W_WIN * y + x * 4, &colour, sizeof(int));
	}
}

double ComputeLighting(t_vect p,t_vect norm, t_light *light)
{
	double i;
	t_vect l;
	double n_dot_l;

	i = 0;
	if (light->type == 'a')
	{
		i += light->intensity;
	}
	else 
	{
		if (light->type == 'p')
			l = minus_v(light->position, p);
		else
			l = light->direction;
		n_dot_l = dot(norm, l);
		if (n_dot_l > 0)
			i += light->intensity * n_dot_l / (vect_len(norm) * vect_len(l));
	}
	return (i);
}

int ret_col_cone(t_window *win, t_cone *Cone)
{
	int ret_col = 0;
	t_vect oc = minus_v(win->O, Cone->center);
	win->p = plus_v(win->O, mult_v(win->closest_d, win->D));
	double m = dot(oc, Cone->v) + dot(win->D, mult_v(win->t1.y,Cone->v));
	win->norm = minus_v(minus_v(win->p, Cone->center),mult_v(m * (1 + (Cone->tang*Cone->tang)),Cone->v));
	win->norm = mult_v((1 / vect_len(win->norm)),win->norm);
	ret_col += (Cone->colour & 255) * ComputeLighting(win->p, win->norm, (t_light *)(win->light->content));
	ret_col += (int)((Cone->colour >> 8 & 255) * ComputeLighting(win->p, win->norm, (t_light *)(win->light->content))) << 8;
	ret_col += (int)((Cone->colour >> 16 & 255) * ComputeLighting(win->p, win->norm, (t_light *)(win->light->content))) << 16;
	return (ret_col);
}
int ret_col_cyl(t_window *win, t_cyl *Cyl)
{
	int ret_col = 0;
	t_vect oc = minus_v(win->O, Cyl->center);
	win->p = plus_v(win->O, mult_v(win->closest_d, win->D));
	double m = dot(oc, Cyl->v) + dot(win->D,mult_v(win->t1.x,Cyl->v));
	win->norm = minus_v(minus_v(win->p, Cyl->center),mult_v(m,Cyl->v));
	win->norm = mult_v((1 / vect_len(win->norm)),win->norm);
	ret_col += (Cyl->colour & 255) * ComputeLighting(win->p, win->norm, (t_light *)(win->light->content));
	ret_col += (int)((Cyl->colour >> 8 & 255) * ComputeLighting(win->p, win->norm, (t_light *)(win->light->content))) << 8;
	ret_col += (int)((Cyl->colour >> 16 & 255) * ComputeLighting(win->p, win->norm, (t_light *)(win->light->content))) << 16;
	return (ret_col);
}
int ret_col_sph(t_window *win, t_sphere *Sphere)
{
	int ret_col = 0;
	win->p = plus_v(win->O, mult_v(win->closest_d, win->D));
	win->norm = minus_v(win->p, Sphere->center);
	win->norm = mult_v((1 / vect_len(win->norm)),win->norm);
	ret_col += (Sphere->colour & 255) * ComputeLighting(win->p, win->norm, (t_light *)(win->light->content));
	ret_col += (int)((Sphere->colour >> 8 & 255) * ComputeLighting(win->p, win->norm, (t_light *)(win->light->content))) << 8;
	ret_col += (int)((Sphere->colour >> 16 & 255) * ComputeLighting(win->p, win->norm, (t_light *)(win->light->content))) << 16;
	return (ret_col);
}
int ret_color(t_window *win, t_list *clos)
{
	int ret_col = 0;
	if (clos->content_size == sizeof(t_cyl))
	{
		ret_col = ret_col_cyl(win,(t_cyl *)(clos->content));
	}
	if(clos->content_size == sizeof(t_sphere))
	{
		ret_col = ret_col_sph(win,(t_sphere *)(clos->content));
	}
	if (clos->content_size == sizeof(t_cone))
	{
		ret_col = ret_col_cone(win,(t_cone *)(clos->content));
	}
	return (ret_col);
}
t_clos		init_clos(t_list *obj)
{
	t_clos	clos;

	clos.obj = obj;
	return (clos);
}
int TraceRay(t_window *win)
{
	int ret_col = 0;
	win->closest_d = 600000.0;
	t_list	*obj;
	t_clos clos = init_clos(NULL);
	obj = win->obj;
	while (obj)
	{
		if (obj->content_size == sizeof(t_cone))
		 	win->t1 = IntersectRayCone(win, obj->content);
		if (obj->content_size == sizeof(t_cyl))
		 	win->t1 = IntersectRayCyl(win, obj->content);
		if (obj->content_size == sizeof(t_sphere))
			win->t1 = IntersectRaySphere(win, obj->content);
   		if (win->t1.x >= 1.0 && win->t1.x <= 600000.0 && win->t1.x < win->closest_d)
		{
			clos.obj = obj;
			clos.closd =  win->t1.x;
			win->closest_d = win->t1.x;
		}
		if (win->t1.y >= 1.0 && win->t1.y <= 600000.0 && win->t1.y < win->closest_d)
		{
			clos.obj = obj;
			clos.closd =  win->t1.y;
			win->closest_d = win->t1.y;
		}
		obj = obj->next;
	}
	if (clos.obj == NULL)
		return (0xFFFFFF);
	ret_col = ret_color(win, clos.obj);
	return (ret_col);
}

t_vect CanvasToViewport(t_window *win)
{
    t_vect a;
    a.x = (double)win->x / W_WIN;
    a.y = (double)win->y / H_WIN;
    a.z = win->dist;
    return (a);
}

void scene1(t_window *win)
{
	win->O.x = 0;
	win->O.y = 0;
	win->O.z = 0;
	win->x = -H_WIN / 2;
	while (win->x < W_WIN / 2)
    {
        win->y = -H_WIN / 2;
        while (win->y < H_WIN / 2)
        {
			win->D = CanvasToViewport(win);
			win->colourput = TraceRay(win);
			pixel_put_img(win, win->x + H_WIN / 2, H_WIN / 2 - win->y - 1, win->colourput);
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
	// if (key == 126)
	// {
	// 	win->Sphere.center.y -= 10;
	// 	scene1(win);
	// }
	// if (key == 125)
	// {
	// 	win->Sphere.center.y += 10;
	// 	scene1(win);
	// }
	// if (key == 123)
	// {
	// 	win->Sphere.center.x += 10;
	// 	scene1(win);
	// }
	// if (key == 124)
	// {
	// 	win->Sphere.center.x -= 10;
	// 	scene1(win);
	// }
	// if (key == 0)
	// {
	// 	win->Sphere.center.z -= 5;
	// 	scene1(win);
	// }
	// if (key == 1)
	// {
	// 	win->Sphere.center.z += 5;
	// 	scene1(win);
	// }
	 return (1);
}

void	loop(t_window *win)
{
	mlx_hook(win->win_ptr, 2, 1L << 0, key_handler, win);
	mlx_loop(win->mlx_ptr);
}

void	initdata(t_window *win)
{
	win->size_line = W_WIN;
	win->bpp = 32;
	win->endian = 0;
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

int main()
{
    t_window *win;
	t_list	*new;
	t_sphere		Sphere;
	t_cyl Cyl;
	t_light light;
	win = (t_window*)malloc(sizeof(t_window));
	win->obj = NULL;
	Sphere.colour = 0x0FF0000;
	Sphere.center.x = 1;
	Sphere.center.y = 0;
	Sphere.center.z = 5;
	Sphere.radius = 1;
	Cyl.colour = 0x0000FF;
	Cyl.center.x = 0;
	Cyl.center.y = 0;
	Cyl.center.z = 5;
	Cyl.radius = 1;
	Cyl.v.x = 1;
	Cyl.v.y = 1;
	Cyl.v.z = 0;
	new = ft_lstnew(&Cyl, sizeof(t_cyl));
	ft_lstadd(&(win->obj), new);
	new = ft_lstnew(&Sphere,sizeof(t_sphere));
	ft_lstadd(&(win->obj), new);
	Sphere.colour = 0x0bac000;
	Sphere.center.x = 1;
	Sphere.center.y = 0;
	Sphere.center.z = 5;
	Sphere.radius = 1;
	// new = ft_lstnew(&Sphere,sizeof(t_sphere));
	// ft_lstadd(&(win->obj), new);
	win->dist = 1;
	light.type = 'p';
	light.position.x =	2;
	light.position.y = 1;
	light.position.z = 0;
	light.intensity = 0.9;
	light.direction.x = -250;
	light.direction.y = -250;
	light.direction.z = 0;
	new = ft_lstnew(&light, sizeof(t_light));
	ft_lstadd(&(win->light), new);
	init(win);
    scene1(win);
	loop(win);
}