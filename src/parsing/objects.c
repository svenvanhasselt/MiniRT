/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:28:44 by svan-has      #+#    #+#                 */
/*   Updated: 2023/11/27 09:14:08 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"

void	parse_sphere(char ***split_line, t_data *data, int i)
{
	if (line_check(split_line) != 7)
		error_exit("Wrong formatting of sphere data");
	data->objects[i].type = sphere;
	data->objects[i].vec.x = string_to_float(split_line[0][0]);
	data->objects[i].vec.y = string_to_float(split_line[0][1]);
	data->objects[i].vec.z = string_to_float(split_line[0][2]);
	data->objects[i].sph_diameter = string_to_float(split_line[1][0]);
	data->objects[i].color.r = string_to_float(split_line[2][0]);
	data->objects[i].color.g = string_to_float(split_line[2][1]);
	data->objects[i].color.b = string_to_float(split_line[2][2]);
}

void	parse_plane(char ***split_line, t_data *data, int i)
{
	if (line_check(split_line) != 9)
		error_exit("Wrong formatting of plane data");
	data->objects[i].type = plane;
	data->objects[i].vec.x = string_to_float(split_line[0][0]);
	data->objects[i].vec.y = string_to_float(split_line[0][1]);
	data->objects[i].vec.z = string_to_float(split_line[0][2]);
	data->objects[i].vec2.x = string_to_float(split_line[1][0]);
	data->objects[i].vec2.y = string_to_float(split_line[1][1]);
	data->objects[i].vec2.z = string_to_float(split_line[1][2]);
	data->objects[i].color.r = string_to_float(split_line[2][0]);
	data->objects[i].color.g = string_to_float(split_line[2][1]);
	data->objects[i].color.b = string_to_float(split_line[2][2]);
}

void	parse_cylinder(char ***split_line, t_data *data, int i)
{
	if (line_check(split_line) != 11)
		error_exit("Wrong formatting of cylinder data");
	data->objects[i].type = cylinder;
	data->objects[i].vec.x = string_to_float(split_line[0][0]);
	data->objects[i].vec.y = string_to_float(split_line[0][1]);
	data->objects[i].vec.z = string_to_float(split_line[0][2]);
	data->objects[i].vec2.x = string_to_float(split_line[1][0]);
	data->objects[i].vec2.y = string_to_float(split_line[1][1]);
	data->objects[i].vec2.z = string_to_float(split_line[1][2]);
	data->objects[i].cyl_diameter = string_to_float(split_line[2][0]);
	data->objects[i].cyl_height = string_to_float(split_line[3][0]);
	data->objects[i].color.r = string_to_float(split_line[4][0]);
	data->objects[i].color.g = string_to_float(split_line[4][1]);
	data->objects[i].color.b = string_to_float(split_line[4][2]);
}
