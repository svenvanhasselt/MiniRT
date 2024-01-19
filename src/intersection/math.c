/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 09:10:52 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/19 14:24:54 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

float	compare_t(float t, float t2)
{
	if (t < 0 && t2 >= 0)
		return (t2);
	else if (t2 < 0 && t >= 0)
		return (t);
	else if (t >= 0 && t2 >= 0)
	{
		if (t < t2)
			return (t);
		else
			return (t2);
	}
	return (-1);
}

void	compare_update_t(t_object *obj, t_ray *ray)
{
	ray->t = compare_t(obj->t, ray->t);
	if (ray->t == obj->t && ray->t >= 0)
		ray->obj = obj;
}

bool	calculate_t_and_m(t_object *obj, t_ray *ray)
{
	if (obj->discrim.d < 0)
	{
		obj->t = -1;
		return (false);
	}
	if (obj->discrim.d >= 0)
	{
		obj->t = (-obj->discrim.b - sqrt(obj->discrim.d))
			/ (2 * obj->discrim.a);
		obj->t2 = (-obj->discrim.b + sqrt(obj->discrim.d))
			/ (2 * obj->discrim.a);
	}
	obj->m1 = dot(ray->dir, obj->vec2) * obj->t
		+ dot(sub(ray->orig, obj->vec), obj->vec2);
	obj->m2 = dot(ray->dir, obj->vec2) * obj->t2
		+ dot(sub(ray->orig, obj->vec), obj->vec2);
	obj->t = compare_t(obj->t, obj->t2);
	if ((obj->m1 <= obj->height / 2 && obj->m1 >= -obj->height / 2)
		|| (obj->m2 <= obj->height / 2 && obj->m2 >= -obj->height / 2))
		return (true);
	obj->t = -1;
	return (false);
}

float	discriminant(float a, float b, float c)
{
	return (b * b - 4 * a * c);
}
