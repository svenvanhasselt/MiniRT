/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 16:47:30 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/19 16:52:46 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

float	hit_cylinder_body(t_object *obj, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	t_vec	oc;

	oc = sub(ray->orig,obj->vec);
	a = dot(ray->dir,ray->dir) - pow(dot(ray->dir, obj->vec2),2);
	b = 2*(dot(ray->dir, oc) - dot(ray->dir, obj->vec2) * dot(oc, obj->vec2));
	c = dot(oc, oc) - pow(dot(oc, obj->vec2), 2) - pow(obj->diameter / 2, 2);
	obj->discrim.d = discriminant(a, b, c);
	if (obj->discrim.d < 0)
		return (-1);
	if (obj->discrim.d >= 0)
	{
		obj->t = (-b - sqrt(obj->discrim.d)) / (2 * a);
		obj->t2 = (-b + sqrt(obj->discrim.d)) /(2 * a);
		if (obj->t <= 0.00f || obj->t2 <= 0.00f)
		{
			// printf("test\n");
			ray->inside = false;
		}
		

	}
	float m1 = dot(ray->dir,obj->vec2) * obj->t + dot(sub(ray->orig,obj->vec), obj->vec2);
	float m2 = dot(ray->dir,obj->vec2) * obj->t2 + dot(sub(ray->orig,obj->vec), obj->vec2);
	obj->t = compare_t(obj->t, obj->t2);
	if((m1 <= obj->height / 2 && m1 >= -obj->height / 2) || (m2 <= obj->height / 2 && m2 >= -obj->height / 2  ))
	{
		if (ray->inside)
			printf("%f, %f\n",obj->t, obj->t2);
		return (obj->t);
	}	
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