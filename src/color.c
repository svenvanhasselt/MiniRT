/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 10:19:24 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/30 17:52:28 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//0x  FF FF FF
//Hex RR GG BB
//converts a color to a uint32_t RGBA(MLX)

float clamp(float value, float min, float max)
{
   if (value < min)
      value = 0.0;
   if (value > max)
      value = 1.0;
   return (value);
}
uint32_t get_rgba(float r, float g, float b, float a)
{
   return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | (uint32_t)a);
}


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
	t_color amb;
   t_color col;
	amb.r = (data->amb_light.color.r * data->amb_light.ambient);
	amb.g = (data->amb_light.color.g * data->amb_light.ambient);
	amb.b = (data->amb_light.color.b * data->amb_light.ambient);



   col = set_col((object.color.r * diffuse), (object.color.g * diffuse), (object.color.b * diffuse));
   col.r += amb.r;
   col.g += amb.g;
   col.b += amb.b;

   col.r = clamp(col.r , 0.0, 1.0);
   col.g = clamp(col.g , 0.0, 1.0);
   col.b = clamp(col.b , 0.0,1.0);

   // gamma correction?
   // col.r = pow(col.r, 1 / 2.2);
   // col.g = pow(col.g, 1 / 2.2);
   // col.b = pow(col.b, 1 / 2.2);

	return (col);
}
