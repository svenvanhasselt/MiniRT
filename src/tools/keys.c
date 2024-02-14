/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:59:01 by svan-has          #+#    #+#             */
/*   Updated: 2024/02/10 16:40:35 by sven             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include <limits.h>

void	change_shape(t_data *data, int axis, float value)
{
	if (data->rotation.obj_type != object || \
	data->rotation.object->type == plane)
		return ;
	if (axis == x_axis && data->rotation.object->type != cone)
		data->rotation.object->diameter = clamp(data->rotation.object->diameter \
		+ value, 0.1f, 1000);
	if (axis == y_axis)
		data->rotation.object->height = clamp(data->rotation.object->height \
		+ value, 0.1f, 1000);
	reset_pix(data);
	calc_viewport(data);
	print_pix(data);
}

void	moving_keys(mlx_key_data_t kd, t_data *data)
{
	(void)kd;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->rotation.action(data, x_axis, -0.3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->rotation.action(data, x_axis, 0.3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->rotation.action(data, y_axis, -0.3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->rotation.action(data, y_axis, 0.3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		data->rotation.action(data, z_axis, -0.3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		data->rotation.action(data, z_axis, 0.3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_COMMA))
		change_shape(data, x_axis, -0.3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_PERIOD))
		change_shape(data, x_axis, 0.3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_SLASH))
		change_shape(data, y_axis, -0.3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_SEMICOLON))
		change_shape(data, y_axis, 0.3);
}

void	change_object(t_data *data)
{
	if (data->rotation.obj_type != object)
		change_type(data, object, NULL);
	else if (data->rotation.object->id + 1 < data->object_num)
		change_type(data, object, \
		&data->objects[data->rotation.object->id + 1]);
	else
		change_type(data, object, &data->objects[0]);
}

void	control_keys(mlx_key_data_t kd, t_data *data)
{
	(void)kd;
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
	{
		data->rotation.action = rotation;
		print_message(data, "Action: Rotation");
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_T))
	{
		data->rotation.action = translation;
		print_message(data, "Action: Translation");
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_C))
		change_type(data, camera, NULL);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_L))
		change_type(data, light, NULL);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_O))
		change_object(data);
}

void	key_press(mlx_key_data_t kd, void *param)
{
	t_data	*data;

	data = param;
	moving_keys(kd, data);
	control_keys(kd, data);
}
