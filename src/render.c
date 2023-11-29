/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 17:47:22 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/29 17:04:57 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>

t_vec	calc_surface_normal(t_vec intersection_point, t_vec oc)
{
	t_vec	surf_norm;
	t_vec	center_to_intersection;

	center_to_intersection = sub(intersection_point, oc);
	surf_norm = unit_vector(center_to_intersection);
	return (surf_norm);
}

float calc_diffuse(t_vec light_pos, t_vec surf_norm, t_vec inter_point, float diffuse_int)
{
	t_vec	norm;
	float	light_dir;

	norm = unit_vector(sub(light_pos, inter_point));
	light_dir = dot(surf_norm, norm);
	if (light_dir < 0)
		light_dir = 0;
	return (clamp(diffuse_int * light_dir, 0.0, 1.0));
}


t_color ray_color(t_ray ray, float t, t_object object, t_data *data)
{
	t_vec	surf_norm;
	float	diffuse;
	t_vec	intersect_p;

	// t_ray light_beam;
	// light_beam.orig = ray.dir;
	// light_beam.dir = 
	// if (hit_sphere(object))
	intersect_p = calc_intersection_point(ray, t);
	surf_norm = calc_surface_normal(intersect_p, object.vec);
	diffuse = calc_diffuse(data->light.vec, surf_norm, intersect_p, data->light.brightness);
	// t_color amb;
	// amb.r = data->amb_light.color.r * data->amb_light.ambient;
	// amb.g = data->amb_light.color.g * data->amb_light.ambient;
	// amb.b = data->amb_light.color.b * data->amb_light.ambient;
	t_color col = set_col((object.color.r * diffuse), (object.color.g * diffuse), (object.color.b * diffuse));
	return (col);
}
