/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopukh <elopukh@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:49:54 by elopukh           #+#    #+#             */
/*   Updated: 2018/11/07 15:49:55 by elopukh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "RTv1.h"
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
t_vect minus_v(t_vect O, t_vect C)
{
    t_vect new;

    new.x = O.x - C.x;
    new.y = O.y - C.y;
    new.z = O.z - C.z;
    return (new);
}
double vect_len(t_vect vect)
{
	double len;
	
	len = sqrt(pow(vect.x,2) + pow(vect.y,2) + pow(vect.z,2));
	return (len);
}

double dot(t_vect a, t_vect b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}