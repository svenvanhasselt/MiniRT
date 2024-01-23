/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 10:19:24 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/23 18:01:21 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float clamp(float value, float min, float max)
{
   if (value < min)
      value = 0.0;
   if (value > max)
      value = 1.0;
   return (value);
}
uint32_t get_rgba(float r, float g, float b)
{
	uint32_t r_new;
	uint32_t g_new;
	uint32_t b_new;

	r_new = r * 255;
	g_new = g * 255;
	b_new = b * 255;
   return (r_new << 24 | g_new << 16 | b_new << 8 | 255);
}


t_vec	calc_surface_normal(t_vec intersection_point, t_vec oc)
{
	t_vec	surf_norm;
	t_vec	center_to_intersection;

	center_to_intersection = sub(intersection_point, oc);
	surf_norm = unit_vector(center_to_intersection);
	return (surf_norm);
}

float calc_diffuse(t_vec light_pos, t_vec surf_norm, t_vec inter_point)
{
	t_vec	norm;
	float	diffuse;

	norm = unit_vector(sub(light_pos, inter_point));
	diffuse = dot(norm, surf_norm); // check if negative
	diffuse = clamp(diffuse, 0.0, 1.0);
	return (diffuse);
}

bool	check_obj(t_data *data, t_ray ray, int id)
{
	int i;

	i = 0;
	while (i < data->object_num)
	{
		if (data->objects[i].type == sphere && hit_sphere(&data->objects[i], &ray) && data->objects[i].id != id)
			return (true);
		else if (data->objects[i].type == plane && hit_plane(&data->objects[i], &ray) && data->objects[i].id != id)
			return (true);
		else if (data->objects[i].type == cylinder && hit_cylinder(&data->objects[i], &ray) && data->objects[i].id != id)
			return (true);
		else if (data->objects[i].type == cone && hit_cone(&data->objects[i], &ray) && data->objects[i].id != id)
			return (true);
		i++;
	}
	return (false);
}

t_vec ray_color(t_ray ray, float t, t_object *object, t_data *data)
{
	t_vec	intersect_p;
	t_vec	surf_norm;
	t_vec	amb;
    t_vec	col = set_vec(0,0,0);
	t_vec	shadow_ray;
	t_vec	light;
	float	diffuse;
	bool	face_out;
	 bool inside = false;

	face_out = true;
	intersect_p = calc_intersection_point(ray, t);
	if (object->type == plane)
	{
		surf_norm = unit_vector(object->vec2);
		if (dot(ray.dir, object->vec2) > 0)
			surf_norm = mult_fact(surf_norm, -1);
	}
	else if (object->type == sphere)//cone shadow is also not right
    {
        surf_norm = unit_vector(sub(object->vec, intersect_p));
        if (dot(ray.dir, surf_norm) > 0)
		{
			surf_norm = mult_fact(surf_norm, -1);
            inside = true;
		}
    }
	else if (object->type == cylinder)
	{
		float t =  dot(sub(intersect_p, object->vec), object->vec2);
		t_vec pt = add(object->vec, mult_fact(object->vec2, t));
		surf_norm = unit_vector(sub(intersect_p, pt));
		if (ray.inside)
			surf_norm = mult_fact(surf_norm, -1.0f);
	}
	else
		surf_norm = calc_surface_normal(intersect_p, object->vec);
	diffuse = calc_diffuse(data->light.vec, surf_norm, intersect_p);
	col = mult_fact(object->color, diffuse);
	amb = mult_fact(data->amb_light.color, data->amb_light.ambient);
	light = mult_fact(data->light.color, data->light.brightness);
	col = add(col, amb); // add brightness light
	col.x = clamp(col.x, 0.0, 1.0);
   	col.y = clamp(col.y, 0.0, 1.0);
   	col.z = clamp(col.z, 0.0, 1.0);
	shadow_ray = unit_vector(sub(data->light.vec, intersect_p));
	if (check_obj(data, set_ray(intersect_p, shadow_ray), object->id) && !inside)
		return (mult_fact(add(set_vec(0,0,0), amb), 2));
   // gamma correction?


	return (col);
}
