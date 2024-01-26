/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 10:19:24 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/26 14:00:39 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	check_obj(t_data *data, t_ray ray, int id)
{
	int	i;

	i = 0;
	while (i < data->object_num)
	{
		if (data->objects[i].type == sphere && \
		hit_sphere(&data->objects[i], &ray) && data->objects[i].id != id)
			return (true);
		else if (data->objects[i].type == plane && \
		hit_plane(&data->objects[i], &ray) && data->objects[i].id != id)
			return (true);
		else if (data->objects[i].type == cylinder && \
		hit_cylinder(&data->objects[i], &ray) && data->objects[i].id != id)
			return (true);
		else if (data->objects[i].type == cone && \
		hit_cone(&data->objects[i], &ray) && data->objects[i].id != id)
			return (true);
		i++;
	}
	return (false);
}

bool	hard_shadow(t_data *data, t_object *object, t_vec hit_point, \
bool inside)
{
	t_vec	shadow_ray;

	shadow_ray = unit_vector(sub(data->light.vec, hit_point));
	if (check_obj(data, set_ray(hit_point, shadow_ray), object->id) && !inside)
		return (true);
	return (false);
}

t_vec	add_shading(t_data *data, t_object *object, t_vec hit_point, \
t_vec surf_norm)
{
	t_vec	col;
	float	diffuse;

	diffuse = calc_diffuse(data->light.vec, surf_norm, hit_point, \
	data->light.brightness);
	col = mult_fact(object->color, diffuse);
	col = add(col, calc_ambient(data, object));
	col.x = clamp(col.x, 0.0, 1.0);
	col.y = clamp(col.y, 0.0, 1.0);
	col.z = clamp(col.z, 0.0, 1.0);
	return (col);
}

t_vec	ray_color(t_ray ray, float t, t_object *object, t_data *data)
{
	t_vec	hit_point;
	t_vec	surf_norm;
	bool	inside;

	inside = false;
	hit_point = calc_intersection_point(ray, t);
	if (object->type == plane)
		surf_norm = norm_plane(ray, object);
	else if (object->type == sphere)
		surf_norm = norm_sphere(ray, object, hit_point);
	else if (object->type == cylinder)
		surf_norm = norm_cylinder(ray, object, hit_point);
	else
		surf_norm = norm_cone(ray, object, hit_point);
	if (hard_shadow(data, object, hit_point, inside))
		return (add(set_vec(0.0f, 0.0f, 0.0f), calc_ambient(data, object)));
	return (add_shading(data, object, hit_point, surf_norm));
}
