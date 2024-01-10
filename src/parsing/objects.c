/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:28:44 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/10 11:06:23 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"


// void	parse_sphere(char ***split_line, t_data *data, int i)
// {
// 	if (line_check(split_line) != 7)
// 		error_exit("Wrong formatting of sphere data");
// 	data->objects[i].type = sphere;
// 	data->objects[i].vec.x = ft_atof(split_line[0][0]);
// 	data->objects[i].vec.y = ft_atof(split_line[0][1]);
// 	data->objects[i].vec.z = ft_atof(split_line[0][2]);
// 	data->objects[i].sph_diameter = ft_atof(split_line[1][0]);
// 	data->objects[i].color.r = ft_atof(split_line[2][0]);
// 	data->objects[i].color.g = ft_atof(split_line[2][1]);
// 	data->objects[i].color.b = ft_atof(split_line[2][2]);
// }

// void	parse_plane(char ***split_line, t_data *data, int i)
// {
// 	if (line_check(split_line) != 9)
// 		error_exit("Wrong formatting of plane data");
// 	data->objects[i].type = plane;
// 	data->objects[i].vec.x = ft_atof(split_line[0][0]);
// 	data->objects[i].vec.y = ft_atof(split_line[0][1]);
// 	data->objects[i].vec.z = ft_atof(split_line[0][2]);
// 	data->objects[i].vec2.x = ft_atof(split_line[1][0]);
// 	data->objects[i].vec2.y = ft_atof(split_line[1][1]);
// 	data->objects[i].vec2.z = ft_atof(split_line[1][2]);
// 	data->objects[i].color.r = ft_atof(split_line[2][0]);
// 	data->objects[i].color.g = ft_atof(split_line[2][1]);
// 	data->objects[i].color.b = ft_atof(split_line[2][2]);
// }

// void	parse_cylinder(char ***split_line, t_data *data, int i)
// {
// 	if (line_check(split_line) != 11)
// 		error_exit("Wrong formatting of cylinder data");
// 	data->objects[i].type = cylinder;
// 	data->objects[i].vec.x = ft_atof(split_line[0][0]);
// 	data->objects[i].vec.y = ft_atof(split_line[0][1]);
// 	data->objects[i].vec.z = ft_atof(split_line[0][2]);
// 	data->objects[i].vec2.x = ft_atof(split_line[1][0]);
// 	data->objects[i].vec2.y = ft_atof(split_line[1][1]);
// 	data->objects[i].vec2.z = ft_atof(split_line[1][2]);
// 	data->objects[i].cyl_diameter = ft_atof(split_line[2][0]);
// 	data->objects[i].cyl_height = ft_atof(split_line[3][0]);
// 	data->objects[i].color.r = ft_atof(split_line[4][0]);
// 	data->objects[i].color.g = ft_atof(split_line[4][1]);
// 	data->objects[i].color.b = ft_atof(split_line[4][2]);
// }


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
	data->objects[i].color.x = ft_atof(split_line[2][0]) / 255;
	data->objects[i].color.y = ft_atof(split_line[2][1]) / 255;
	data->objects[i].color.z = ft_atof(split_line[2][2]) / 255;
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
	data->objects[i].vec2.x = ft_atof(split_line[1][0]);
	data->objects[i].vec2.y = ft_atof(split_line[1][1]);
	data->objects[i].vec2.z = ft_atof(split_line[1][2]);
	data->objects[i].color.x = ft_atof(split_line[2][0]) / 255;
	data->objects[i].color.y = ft_atof(split_line[2][1]) / 255;
	data->objects[i].color.z = ft_atof(split_line[2][2]) / 255;
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
	data->objects[i].vec2.x = ft_atof(split_line[1][0]);
	data->objects[i].vec2.y = ft_atof(split_line[1][1]);
	data->objects[i].vec2.z = ft_atof(split_line[1][2]);
	data->objects[i].diameter = ft_atof(split_line[2][0]);
	data->objects[i].height = ft_atof(split_line[3][0]);
	data->objects[i].color.x = ft_atof(split_line[4][0]) / 255;
	data->objects[i].color.y = ft_atof(split_line[4][1]) / 255;
	data->objects[i].color.z = ft_atof(split_line[4][2]) / 255;
}

void	parse_cone(char ***split_line, t_data *data, int i)
{
	if (line_check(split_line) != 10)
		error_exit("Wrong formatting of cone data");
	data->objects[i].id = i;
	data->objects[i].type = cone;
	data->objects[i].vec.x = ft_atof(split_line[0][0]);
	data->objects[i].vec.y = ft_atof(split_line[0][1]);
	data->objects[i].vec.z = ft_atof(split_line[0][2]);
	data->objects[i].vec2.x = ft_atof(split_line[1][0]);
	data->objects[i].vec2.y = ft_atof(split_line[1][1]);
	data->objects[i].vec2.z = ft_atof(split_line[1][2]);
	data->objects[i].k = ft_atof(split_line[2][0]);
	data->objects[i].color.x = ft_atof(split_line[3][0]) / 255;
	data->objects[i].color.y = ft_atof(split_line[3][1]) / 255;
	data->objects[i].color.z = ft_atof(split_line[3][2]) / 255;
}
