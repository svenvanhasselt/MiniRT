/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 12:35:41 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/31 14:52:48 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_vec	norm_sphere(t_ray *ray, t_object *object, t_vec hit_point)
{
	t_vec	surf_norm;

	surf_norm = unit_vector(sub(object->vec, hit_point));
	if (dot(ray->dir, surf_norm) > 0)
	{
		surf_norm = mult_fact(surf_norm, -1);
		ray->inside = true;
	}
	return (surf_norm);
}

t_vec	norm_cylinder(t_ray ray, t_object *object, t_vec hit_point)
{
	t_vec	surf_norm;
	t_vec	pt;
	float	t;

	t = dot(sub(hit_point, object->vec), object->vec2);
	pt = add(object->vec, mult_fact(object->vec2, t));
	surf_norm = unit_vector(sub(hit_point, pt));
	if (ray.inside)
		surf_norm = mult_fact(surf_norm, -1.0f);
	return (surf_norm);
}

t_vec	norm_cone(t_ray ray, t_object *object, t_vec hit_point)
{
	t_vec	surf_norm;
	t_vec	pt;
	float	t;

	t = dot(sub(hit_point, object->vec), object->vec2);
	pt = add(object->vec, mult_fact(object->vec2, t));
	surf_norm = unit_vector(sub(hit_point, pt));
	if (ray.inside)
		surf_norm = mult_fact(surf_norm, -1.0f);
	return (surf_norm);
}

t_vec	norm_plane(t_ray ray, t_object *object)
{
	t_vec	surf_norm;

	(void)ray;
	surf_norm = unit_vector(object->vec2);
	//if (ray.inside)
	//	surf_norm = mult_fact(surf_norm, -1);
	return (surf_norm);
}
