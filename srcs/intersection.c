/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <elopukh@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:45:47 by elopukh           #+#    #+#             */
/*   Updated: 2018/11/07 15:45:48 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "RTv1.h"

t_vect IntersectRaySphere(t_window *win, t_sphere *Sphere)
{
	t_vect oc = minus_v(win->O, Sphere->center);
	t_vect ret;
    double k1 = dot(win->D, win->D);
    double k2 = 2.0 * dot(oc, win->D);
    double k3 = dot(oc, oc) - Sphere->radius * Sphere->radius;
    double discriminant = k2*k2 - 4*k1*k3;
	if (discriminant < 0)
	{
		ret.x = 600000.0;
		ret.y = 600000.0;
		ret.z = 600000.0;
		return (ret);
	}
	ret.x = (-k2 + sqrt(discriminant)) / (2 * k1);
	ret.y = (-k2 - sqrt(discriminant)) / (2 * k1);
	ret.z = 0;
    return (ret);
}

t_vect IntersectRayCyl(t_window *win, t_cyl *Cyl)
{
	t_vect oc = minus_v(win->O, Cyl->center);
	t_vect ret;
	Cyl->v = mult_v((1 / vect_len(Cyl->v)),Cyl->v);
    double k1 = dot(win->D, win->D) - (dot(win->D, Cyl->v) * dot(win->D, Cyl->v));
    double k2 = 2.0 *(dot(oc, win->D) - dot(oc, Cyl->v) * dot(win->D,Cyl->v));
    double k3 = dot(oc, oc) - pow(dot(oc, Cyl->v),2) - Cyl->radius * Cyl->radius;
    double discriminant = k2*k2 - 4*k1*k3;
	if (discriminant < 0)
	{
		ret.x = 600000.0;
		ret.y = 600000.0;
		ret.z = 600000.0;
		return (ret);
	}
	ret.x = (-k2 + sqrt(discriminant)) / (2 * k1);
	ret.y = (-k2 - sqrt(discriminant)) / (2 * k1);
	ret.z = 0;
    return (ret);
}
t_vect IntersectRayCone(t_window *win, t_cone *Cone)
{
	t_vect oc = minus_v(win->O, Cone->center);
	t_vect ret;
	Cone->v = mult_v((1 / vect_len(Cone->v)),Cone->v);
	// double k1 = pow(dot(win->D,Cone->v),2)-pow(cos(Cone->tang),2);
	// double k2 = 2 *(dot(win->D,Cone->v)*dot(Cone->v,oc) - dot(win->D,oc)*pow(cos(Cone->tang),2));
	// double k3 = pow(dot(oc,Cone->v),2) - dot(oc,oc)*pow(cos(Cone->tang),2);
	double k1 = dot(win->D, win->D) - dot(win->D, Cone->v) * dot(win->D, Cone->v);
	double k2 = 2 * (dot(win->D, oc) - dot(win->D, Cone->v) * (dot(oc, Cone->v) + 2 * Cone->tang));
	double k3 = dot(oc, oc) - dot(oc, Cone->v) * (dot(oc, Cone->v) +  4 * Cone->tang);
    double discriminant = k2*k2 - 4*k1*k3;
	if (discriminant < 0)
	{
		ret.x = 600000.0;
		ret.y = 600000.0;
		ret.z = 600000.0;
		return (ret);
	}
	ret.x = (-k2 + sqrt(discriminant)) / (2 * k1);
	ret.y = (-k2 - sqrt(discriminant)) / (2 * k1);
	ret.z = 0;
    return (ret);
}