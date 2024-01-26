/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translation.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 11:03:07 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/26 11:26:07 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	translate_camera(t_data *data, int axis, float value)
{
	if (axis == x_axis)
		data->camera.vec.x += value;
	else if (axis == y_axis)
		data->camera.vec.y += value;
	else if (axis == z_axis)
		data->camera.vec.z += value;
}

void	translate_light(t_data *data, int axis, float value)
{
	if (axis == x_axis)
		data->light.vec.x += value * 5;
	else if (axis == y_axis)
		data->light.vec.y += value * 5;
	else if (axis == z_axis)
		data->light.vec.z += value * 5;
}

void	translate_object(t_data *data, int axis, float value)
{
	if (axis == x_axis)
		data->rotation.object->vec.x += value;
	else if (axis == y_axis)
		data->rotation.object->vec.y += value;
	else if (axis == z_axis)
		data->rotation.object->vec.z += value;
}

void	translation(t_data *data, int axis, float value)
{
	if (data->rotation.obj_type == camera)
		translate_camera(data, axis, value);
	else if (data->rotation.obj_type == light)
		translate_light(data, axis, value);
	else if (data->rotation.obj_type == object)
		translate_object(data, axis, value);
	reset_pix(data);
	calc_viewport(data);
	print_pix(data);
}
