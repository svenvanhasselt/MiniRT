/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:28:44 by svan-has          #+#    #+#             */
/*   Updated: 2024/02/05 14:24:29 by sven             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"

void	parse_sphere(char ***split_line, t_data *data, int i)
{
	if (line_check(split_line) != 7)
		error_exit("Wrong formatting of sphere data");
	data->objects[i].id = i;
	data->objects[i].type = sphere;
	data->objects[i].vec.x = ft_atof(split_line[0][0]);
	data->objects[i].vec.y = ft_atof(split_line[0][1]);
	data->objects[i].vec.z = ft_atof(split_line[0][2]);
	data->objects[i].diameter = ft_atof(split_line[1][0]);
	data->objects[i].color.x = check_v(ft_atof(split_line[2][0]), 0, 255) / 255;
	data->objects[i].color.y = check_v(ft_atof(split_line[2][1]), 0, 255) / 255;
	data->objects[i].color.z = check_v(ft_atof(split_line[2][2]), 0, 255) / 255;
}

void	parse_plane(char ***split_line, t_data *data, int i)
{
	if (line_check(split_line) != 9)
		error_exit("Wrong formatting of plane data");
	data->objects[i].id = i;
	data->objects[i].type = plane;
	data->objects[i].vec.x = ft_atof(split_line[0][0]);
	data->objects[i].vec.y = ft_atof(split_line[0][1]);
	data->objects[i].vec.z = ft_atof(split_line[0][2]);
	data->objects[i].vec2.x = check_v(ft_atof(split_line[1][0]), -1, 1);
	data->objects[i].vec2.y = check_v(ft_atof(split_line[1][1]), -1, 1);
	data->objects[i].vec2.z = check_v(ft_atof(split_line[1][2]), -1, 1);
	data->objects[i].color.x = check_v(ft_atof(split_line[2][0]), 0, 255) / 255;
	data->objects[i].color.y = check_v(ft_atof(split_line[2][1]), 0, 255) / 255;
	data->objects[i].color.z = check_v(ft_atof(split_line[2][2]), 0, 255) / 255;
}

void	parse_cylinder(char ***split_line, t_data *data, int i)
{
	if (line_check(split_line) != 11)
		error_exit("Wrong formatting of cylinder data");
	data->objects[i].id = i;
	data->objects[i].type = cylinder;
	data->objects[i].vec.x = ft_atof(split_line[0][0]);
	data->objects[i].vec.y = ft_atof(split_line[0][1]);
	data->objects[i].vec.z = ft_atof(split_line[0][2]);
	data->objects[i].vec2.x = check_v(ft_atof(split_line[1][0]), -1, 1);
	data->objects[i].vec2.y = check_v(ft_atof(split_line[1][1]), -1, 1);
	data->objects[i].vec2.z = check_v(ft_atof(split_line[1][2]), -1, 1);
	data->objects[i].diameter = ft_atof(split_line[2][0]);
	data->objects[i].height = ft_atof(split_line[3][0]);
	data->objects[i].color.x = check_v(ft_atof(split_line[4][0]), 0, 255) / 255;
	data->objects[i].color.y = check_v(ft_atof(split_line[4][1]), 0, 255) / 255;
	data->objects[i].color.z = check_v(ft_atof(split_line[4][2]), 0, 255) / 255;
}

void	parse_cone(char ***split_line, t_data *data, int i)
{
	if (line_check(split_line) != 12)
		error_exit("Wrong formatting of cone data");
	data->objects[i].id = i;
	data->objects[i].type = cone;
	data->objects[i].vec.x = ft_atof(split_line[0][0]);
	data->objects[i].vec.y = ft_atof(split_line[0][1]);
	data->objects[i].vec.z = ft_atof(split_line[0][2]);
	data->objects[i].vec2.x = check_v(ft_atof(split_line[1][0]), -1, 1);
	data->objects[i].vec2.y = check_v(ft_atof(split_line[1][1]), -1, 1);
	data->objects[i].vec2.z = check_v(ft_atof(split_line[1][2]), -1, 1);
	data->objects[i].k = ft_atof(split_line[2][0]);
	data->objects[i].height = ft_atof(split_line[3][0]);
	data->objects[i].angle = ft_atof(split_line[4][0]);
	data->objects[i].color.x = check_v(ft_atof(split_line[5][0]), 0, 255) / 255;
	data->objects[i].color.y = check_v(ft_atof(split_line[5][1]), 0, 255) / 255;
	data->objects[i].color.z = check_v(ft_atof(split_line[5][2]), 0, 255) / 255;
}
