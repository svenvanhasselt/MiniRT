/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotation.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 10:59:58 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/26 11:59:35 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	rotate_object(t_data *data, int axis, float value)
{
	t_quat	rotate;
	float	sin_value;
	float	cos_value;

	sin_value = sin(value);
	cos_value = cos(value);
	rotate = set_quat(0, 0, 0, 0);
	if (axis == x_axis)
		rotate = set_quat(cos_value, 0, sin_value, 0);
	else if (axis == y_axis)
		rotate = set_quat(cos_value, sin_value, 0, 0);
	else if (axis == z_axis)
		rotate = set_quat(cos_value, 0, 0, sin_value);
	data->rotation.object->vec2 = unit_vector(\
	rotate_vector(data->rotation.object->vec2, rotate));
	printf("x: %f y: %f z: %f\n", data->rotation.object->vec2.x, data->rotation.object->vec2.y, data->rotation.object->vec2.z);
}

void	rotate_camera(t_data *data, int axis, float value)
{
	if (axis == x_axis)
		data->camera.ovec.x += value;
	if (axis == y_axis)
		data->camera.ovec.y += value;
	if (axis == z_axis)
		data->camera.ovec.z += value;
}

void	rotation(t_data *data, int axis, float value)
{
	if (data->rotation.obj_type == light)
		return ;
	if (data->rotation.obj_type == object)
		rotate_object(data, axis, value);
	if (data->rotation.obj_type == camera && (axis == x_axis || axis == y_axis))
		rotate_camera(data, axis, value);
	reset_pix(data);
	calc_viewport(data);
	print_pix(data);
}

t_vec	rotate_vector(t_vec vec, t_quat r)
{
	t_vec	rotated_vector;
	t_quat	vec_quat;
	t_quat	rot_quat;

	vec_quat = set_quat (0, vec.x, vec.y, vec.z);
	rot_quat = set_quat (\
	r.a * vec_quat.a - r.b * vec_quat.b - r.c * vec_quat.c - r.d * vec_quat.d, \
	r.a * vec_quat.b + r.b * vec_quat.a + r.c * vec_quat.d - r.d * vec_quat.c, \
	r.a * vec_quat.c - r.b * vec_quat.d + r.c * vec_quat.a + r.d * vec_quat.b, \
	r.a * vec_quat.d + r.b * vec_quat.c - r.c * vec_quat.b + r.d * vec_quat.a \
	);
	rot_quat = unit_quat(rot_quat);
	rotated_vector = set_vec(rot_quat.b, rot_quat.c, rot_quat.d);
	return (rotated_vector);
}
