/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 13:54:09 by svan-has      #+#    #+#                 */
/*   Updated: 2023/11/23 15:31:59 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"

void	parse_amb_light(char ***split_line, t_data *data)
{
	if (line_check(split_line) != 4)
		error_exit("Wrong formatting of ambient light data");
	data->amb_light.ambient = string_to_float(split_line[0][0]);
	data->amb_light.color.r = string_to_float(split_line[1][0]);
	data->amb_light.color.g = string_to_float(split_line[1][1]);
	data->amb_light.color.b = string_to_float(split_line[1][2]);
}

void	parse_camera(char ***split_line, t_data *data)
{
	if (line_check(split_line) != 7)
		error_exit("Wrong formatting of camera data");
	data->camera.vec.x = string_to_float(split_line[0][0]);
	data->camera.vec.y = string_to_float(split_line[0][1]);
	data->camera.vec.z = string_to_float(split_line[0][2]);
	data->camera.ov_x = string_to_float(split_line[1][0]);
	data->camera.ov_y = string_to_float(split_line[1][1]);
	data->camera.ov_z = string_to_float(split_line[1][2]);
	data->camera.fov = string_to_float(split_line[2][0]);
}

void	parse_light(char ***split_line, t_data *data)
{
	if (line_check(split_line) != 7)
		error_exit("Wrong formatting of light data");
	data->light.vec.x = string_to_float(split_line[0][0]);
	data->light.vec.y = string_to_float(split_line[0][1]);
	data->light.vec.z = string_to_float(split_line[0][2]);
	data->light.brightness = string_to_float(split_line[1][0]);
	data->light.color.r = string_to_float(split_line[2][0]);
	data->light.color.g = string_to_float(split_line[2][1]);
	data->light.color.b = string_to_float(split_line[2][2]);
}
