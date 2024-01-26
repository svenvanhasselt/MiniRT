/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 10:59:01 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/26 12:49:19 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	moving_keys(mlx_key_data_t kd, t_data *data)
{
	kd.key = 0;
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
}

void	control_keys(mlx_key_data_t kd, t_data *data)
{
	kd.key = 0;
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
		change_object(data, camera, NULL);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_L))
		change_object(data, light, NULL);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_O))
	{
		if (data->rotation.obj_type != object)
			change_object(data, object, NULL);
		else if (data->rotation.object->id + 1 < data->object_num)
			change_object(data, object, &data->objects[data->rotation.object->id + 1]);
		else
			change_object(data, object, &data->objects[0]);
	}
}

void	key_press(mlx_key_data_t kd, void *param)
{
	t_data	*data;

	data = param;
	moving_keys(kd, data);
	control_keys(kd, data);
}
