/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:28:44 by svan-has          #+#    #+#             */
/*   Updated: 2023/12/19 17:00:08 by sven             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"

void	parse_sphere(char ***split_line, t_data *data, int i)
{
	if (line_check(split_line) != 7)
		error_exit("Wrong formatting of sphere data");
	data->objects[i].type = sphere;
	data->objects[i].vec.x = ft_atof(split_line[0][0]);
	data->objects[i].vec.y = ft_atof(split_line[0][1]);
	data->objects[i].vec.z = ft_atof(split_line[0][2]);
	data->objects[i].sph_diameter = ft_atof(split_line[1][0]);
	data->objects[i].color.r = ft_atof(split_line[2][0]);
	data->objects[i].color.g = ft_atof(split_line[2][1]);
	data->objects[i].color.b = ft_atof(split_line[2][2]);
}

void	parse_plane(char ***split_line, t_data *data, int i)
{
	if (line_check(split_line) != 9)
		error_exit("Wrong formatting of plane data");
	data->objects[i].type = plane;
	data->objects[i].vec.x = ft_atof(split_line[0][0]);
	data->objects[i].vec.y = ft_atof(split_line[0][1]);
	data->objects[i].vec.z = ft_atof(split_line[0][2]);
	data->objects[i].vec2.x = ft_atof(split_line[1][0]);
	data->objects[i].vec2.y = ft_atof(split_line[1][1]);
	data->objects[i].vec2.z = ft_atof(split_line[1][2]);
	data->objects[i].color.r = ft_atof(split_line[2][0]);
	data->objects[i].color.g = ft_atof(split_line[2][1]);
	data->objects[i].color.b = ft_atof(split_line[2][2]);
}

void	parse_cylinder(char ***split_line, t_data *data, int i)
{
	if (line_check(split_line) != 11)
		error_exit("Wrong formatting of cylinder data");
	data->objects[i].type = cylinder;
	data->objects[i].vec.x = ft_atof(split_line[0][0]);
	data->objects[i].vec.y = ft_atof(split_line[0][1]);
	data->objects[i].vec.z = ft_atof(split_line[0][2]);
	data->objects[i].vec2.x = ft_atof(split_line[1][0]);
	data->objects[i].vec2.y = ft_atof(split_line[1][1]);
	data->objects[i].vec2.z = ft_atof(split_line[1][2]);
	data->objects[i].cyl_diameter = ft_atof(split_line[2][0]);
	data->objects[i].cyl_height = ft_atof(split_line[3][0]);
	data->objects[i].color.r = ft_atof(split_line[4][0]);
	data->objects[i].color.g = ft_atof(split_line[4][1]);
	data->objects[i].color.b = ft_atof(split_line[4][2]);
}
