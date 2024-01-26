/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 11:35:54 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/26 16:00:25 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_vec	calc_surface_normal(t_vec intersection_point, t_vec oc)
{
	t_vec	surf_norm;
	t_vec	center_to_intersection;

	center_to_intersection = sub(intersection_point, oc);
	surf_norm = unit_vector(center_to_intersection);
	return (surf_norm);
}

float	calc_diffuse(t_vec light_pos, t_vec surf_norm, t_vec inter_point, \
float brightness)
{
	t_vec	norm;
	float	diffuse;

	norm = unit_vector(sub(light_pos, inter_point));
	diffuse = dot(norm, surf_norm);
	diffuse = clamp(diffuse, 0.0, 1.0);
	return (diffuse * brightness);
}

t_vec	calc_ambient(t_data *data, t_object *object)
{
	t_vec	amb;

	amb = mult(object->color, data->amb_light.color);
	amb = mult_fact(amb, data->amb_light.ambient);
	return (amb);
}

float	clamp(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}

uint32_t	get_rgba(float r, float g, float b)
{
	uint32_t	r_new;
	uint32_t	g_new;
	uint32_t	b_new;

	r_new = r * 255;
	g_new = g * 255;
	b_new = b * 255;
	return (r_new << 24 | g_new << 16 | b_new << 8 | 255);
}
