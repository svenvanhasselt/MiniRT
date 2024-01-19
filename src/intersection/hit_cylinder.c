/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 16:47:30 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/19 13:46:06 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

float	hit_cylinder_body(t_object *obj, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t;
	float	t2;
	t_vec	oc;

	t = -1;
	t2 = -1;
	// printf("x:%f y:%f z:%f\n", obj->vec2.x, obj->vec2.y,obj->vec2.z);//vec don't have negative number
	oc = sub(ray->orig,obj->vec);
	a = dot(ray->dir,ray->dir) - pow(dot(ray->dir, obj->vec2),2);
	b = 2*(dot(ray->dir, oc) - dot(ray->dir, obj->vec2) * dot(oc, obj->vec2));
	c = dot(oc, oc) - pow(dot(oc, obj->vec2), 2) - pow(obj->diameter / 2, 2);
	
	//Calculate the discriminant
	discriminant = b*b - 4*a*c;
	if (discriminant < 0)
		return (-1);
	//Calculate the two possible t values
	if (discriminant >= 0)
	{
		t = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) /(2 * a);
	}
	
	// m is a scalar that determines the closet point on the axis to the hit point.
	float m1 = dot(ray->dir,obj->vec2) * t + dot(sub(ray->orig,obj->vec), obj->vec2);
	float m2 = dot(ray->dir,obj->vec2) * t2 + dot(sub(ray->orig,obj->vec), obj->vec2);
	t = compare_t(t, t2);

	//Check if the intersection point is within the height on the cylinder
	if((m1 <= obj->height / 2 && m1 >= -obj->height / 2) || (m2 <= obj->height / 2 && m2 >= -obj->height / 2 ))
		return (t);
	return (-1);//not intersects
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