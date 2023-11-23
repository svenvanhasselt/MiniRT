/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 17:47:22 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/23 16:31:33 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>

float	calc_length(t_vec v)
{
	return (sqrt(dot(v, v)));
}

t_vec	normalize(t_vec cti)
{
	t_vec norm;
	float length;

	length = calc_length(cti);
	if (length != 0)
	norm.x = cti.x / length;
	norm.y = cti.y / length;
	norm.z = cti.z / length;
	return (norm);
}
t_vec	calc_surface_normal(t_vec intersection_point, t_vec oc)
{
	t_vec	surf_norm;
	t_vec	center_to_intersection;

	center_to_intersection = sub(intersection_point, oc);
	surf_norm = normalize(center_to_intersection);
	return (surf_norm);
}

float calc_diffuse(t_vec light_pos, t_vec surf_norm, t_vec inter_point, float diffuse_int)
{
	t_vec	norm;
	float	cos_light_dir;

	norm = normalize(sub(light_pos, inter_point));
	cos_light_dir = dot(surf_norm, norm);
	if (cos_light_dir < 0)
		cos_light_dir = 0;
	return (diffuse_int * cos_light_dir);
}


t_vec	calc_intersection_point(t_ray r, float t)
{
	t_vec	intersection_point;

	intersection_point.x = r.orig.x + t * r.dir.x;
	intersection_point.y = r.orig.y + t * r.dir.y;
	intersection_point.z = r.orig.z + t * r.dir.z;
	return (intersection_point);
}
t_color ray_color(t_ray r, float t, t_vec oc)
{
	t_vec	surf_norm;
	t_vec	light_pos = {0, 0.8, -3};
	float	diffuse_intensity = 2.0;
	float	diffuse_shading;
	t_vec	intersection_point;

	intersection_point = calc_intersection_point(r, t);
	surf_norm = calc_surface_normal(intersection_point, oc);
	diffuse_shading = calc_diffuse(light_pos, surf_norm, intersection_point, diffuse_intensity);
	
	
						//the close point on the sphere, and the center of sphere
		
		t_vec u = oc;
		return set_col((u.x * diffuse_shading*0.05), (u.y * diffuse_shading*0.05), (u.z * diffuse_shading*0.05));//color range base on the unit_vector
	
	// {					//the close point on the sphere, and the center of sphere
	// 	t_vec u = unit_vector(sub(t_to_vec(t, r), oc));
	// 	return set_col(0.5 * (u.x + 1), 0.5 * (u.y + 1), 0.5 * (u.z + 1));//color range base on the unit_vector
	// }
	//t_vec unit_direction = unit_vector(r.dir);
	//float  a = 0.5 * (unit_direction.y + 1.0);
	//return (set_col((1.0 - a) + a * 0.5, (1.0 - a) + a * 0.7, (1.0 - a) + a * 1.0));
}

// t_vec random_unit_vec()
// {
// 	return 
// }
