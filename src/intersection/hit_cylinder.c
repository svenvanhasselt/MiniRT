/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 16:47:30 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/19 14:26:52 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

float	hit_cylinder_body(t_object *obj, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	float	t;
	float	t2;
	t_vec	oc;

	t = -1;
	t2 = -1;
	oc = sub(ray->orig,obj->vec);
	a = dot(ray->dir,ray->dir) - pow(dot(ray->dir, obj->vec2),2);
	b = 2*(dot(ray->dir, oc) - dot(ray->dir, obj->vec2) * dot(oc, obj->vec2));
	c = dot(oc, oc) - pow(dot(oc, obj->vec2), 2) - pow(obj->diameter / 2, 2);
	obj->discrim.d = discriminant(a, b, c);
	if (obj->discrim.d < 0)
		return (-1);
	if (obj->discrim.d >= 0)
	{
		t = (-b - sqrt(obj->discrim.d)) / (2 * a);
		t2 = (-b + sqrt(obj->discrim.d)) /(2 * a);
	}
	float m1 = dot(ray->dir,obj->vec2) * t + dot(sub(ray->orig,obj->vec), obj->vec2);
	float m2 = dot(ray->dir,obj->vec2) * t2 + dot(sub(ray->orig,obj->vec), obj->vec2);
	t = compare_t(t, t2);
	if((m1 <= obj->height / 2 && m1 >= -obj->height / 2) || (m2 <= obj->height / 2 && m2 >= -obj->height / 2 ))
		return (t);
	return (-1);
}

bool	hit_cylinder(t_object *obj, t_ray *ray)
{
	float	t;
	float	t2;
	
	t = hit_cylinder_caps(obj,ray);
	t2 = hit_cylinder_body(obj,ray);
	obj->t = t2;//compare_t(t, t2);
	if (obj->t > 0)
		return (true);
	return(false);
}