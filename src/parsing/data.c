/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 13:54:09 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/10 10:45:01 by svan-has      ########   odam.nl         */
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
	data->amb_light.ambient = ft_atof(split_line[0][0]);
	data->amb_light.color.x = ft_atof(split_line[1][0]) / 255;
	data->amb_light.color.y = ft_atof(split_line[1][1]) / 255;
	data->amb_light.color.z = ft_atof(split_line[1][2]) / 255;
}

void	parse_camera(char ***split_line, t_data *data)
{
	if (line_check(split_line) != 7)
		error_exit("Wrong formatting of camera data");
	data->camera.vec.x = ft_atof(split_line[0][0]);
	data->camera.vec.y = ft_atof(split_line[0][1]);
	data->camera.vec.z = ft_atof(split_line[0][2]);
	data->camera.ovec.x = ft_atof(split_line[1][0]);
	data->camera.ovec.y = ft_atof(split_line[1][1]);
	data->camera.ovec.z = ft_atof(split_line[1][2]);
	data->camera.fov = ft_atof(split_line[2][0]);
	printf("cam z: %f\n", data->camera.vec.z);
}

void	parse_light(char ***split_line, t_data *data)
{
	if (line_check(split_line) != 7)
		error_exit("Wrong formatting of light data");
	data->light.vec.x = ft_atof(split_line[0][0]);
	data->light.vec.y = ft_atof(split_line[0][1]);
	data->light.vec.z = ft_atof(split_line[0][2]);
	data->light.brightness = ft_atof(split_line[1][0]);
	data->light.color.x = ft_atof(split_line[2][0]) / 255;
	data->light.color.y = ft_atof(split_line[2][1]) / 255;
	data->light.color.z = ft_atof(split_line[2][2]) / 255;
}
