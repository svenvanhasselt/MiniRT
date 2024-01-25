/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 13:54:09 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/25 15:29:23 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"

void	parse_resolution(char ***split_line, t_data *data)
{
	if (line_check(split_line) < 2)
		error_exit("Wrong formatting of resolution data");
	data->viewport_w = ft_atof(split_line[0][0]);
	data->viewport_h = ft_atof(split_line[1][0]);
}

void	parse_amb_light(char ***split_line, t_data *data)
{
	if (line_check(split_line) != 4)
		error_exit("Wrong formatting of ambient light data");
	data->amb_light.ambient = check_v(ft_atof(split_line[0][0]), 0, 1);
	data->amb_light.color.x = check_v(ft_atof(split_line[1][0]), 0, 255) / 255;
	data->amb_light.color.y = check_v(ft_atof(split_line[1][1]), 0, 255) / 255;
	data->amb_light.color.z = check_v(ft_atof(split_line[1][2]), 0, 255) / 255;
}

void	parse_camera(char ***split_line, t_data *data)
{
	if (line_check(split_line) != 7)
		error_exit("Wrong formatting of camera data");
	data->camera.vec.x = ft_atof(split_line[0][0]);
	data->camera.vec.y = ft_atof(split_line[0][1]);
	data->camera.vec.z = ft_atof(split_line[0][2]);
	data->camera.ovec.x = check_v(ft_atof(split_line[1][0]), 0, 1);
	data->camera.ovec.y = check_v(ft_atof(split_line[1][1]), 0, 1);
	data->camera.ovec.z = check_v(ft_atof(split_line[1][2]), 0, 1);
	data->camera.fov = check_v(ft_atof(split_line[2][0]), 0, 180);
}

void	parse_light(char ***split_line, t_data *data)
{
	if (line_check(split_line) != 7)
		error_exit("Wrong formatting of light data");
	data->light.vec.x = ft_atof(split_line[0][0]);
	data->light.vec.y = ft_atof(split_line[0][1]);
	data->light.vec.z = ft_atof(split_line[0][2]);
	data->light.brightness = check_v(ft_atof(split_line[1][0]), 0, 1);
	data->light.color.x = check_v(ft_atof(split_line[2][0]), 0, 255) / 255;
	data->light.color.y = check_v(ft_atof(split_line[2][1]), 0, 255) / 255;
	data->light.color.z = check_v(ft_atof(split_line[2][2]), 0, 255) / 255;
}
