/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 16:47:30 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/23 15:51:03 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

float	hit_cylinder_body(t_object *obj, t_ray *ray)
{
	t_vec	oc;

	oc = sub(ray->orig, obj->vec);
	obj->discrim.a = dot(ray->dir, ray->dir)
		- pow(dot(ray->dir, obj->vec2), 2);
	obj->discrim.b = 2 * (dot(ray->dir, oc)
			- dot(ray->dir, obj->vec2) * dot(oc, obj->vec2));
	obj->discrim.c = dot(oc, oc)
		- pow(dot(oc, obj->vec2), 2)
		- pow(obj->diameter / 2, 2);
	obj->discrim.d = discriminant(obj->discrim.a,
			obj->discrim.b, obj->discrim.c);
	calculate_t_and_m(obj, ray);
	return (obj->t);
}

bool	hit_cylinder(t_object *obj, t_ray *ray)
{
	float	t;
	float	t2;

	t = hit_cylinder_caps(obj, ray);
	t2 = hit_cylinder_body(obj, ray);
	obj->t = t2;//compare_t(t, t2);
	if (obj->t > 0)
		return (true);
	return (false);
}
