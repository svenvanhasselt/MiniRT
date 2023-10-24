/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:28:44 by svan-has      #+#    #+#                 */
/*   Updated: 2023/10/24 17:51:40 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"

void    parse_sphere(char ***split_line, t_data *data, int i)
{
    if (line_check(split_line) != 7)
        error_exit("Wrong formatting of sphere data");
    data->objects[i].type = sphere;
    data->objects[i].x = string_to_float(split_line[0][0]);
    data->objects[i].y = string_to_float(split_line[0][1]);
    data->objects[i].z = string_to_float(split_line[0][2]);
    data->objects[i].sph_diameter = string_to_float(split_line[1][0]);
    data->objects[i].r = string_to_float(split_line[2][0]);
    data->objects[i].g = string_to_float(split_line[2][1]);
    data->objects[i].b = string_to_float(split_line[2][2]);
}

void    parse_plane(char ***split_line, t_data *data, int i)
{
    if (line_check(split_line) != 9)
        error_exit("Wrong formatting of plane data");
    data->objects[i].type = plane;
    data->objects[i].x = string_to_float(split_line[0][0]);
    data->objects[i].y = string_to_float(split_line[0][1]);
    data->objects[i].z = string_to_float(split_line[0][2]);
    data->objects[i].vec_x = string_to_float(split_line[1][0]);
    data->objects[i].vec_y = string_to_float(split_line[1][1]);
    data->objects[i].vec_z = string_to_float(split_line[1][2]);
    data->objects[i].r = string_to_float(split_line[2][0]);
    data->objects[i].g = string_to_float(split_line[2][1]);
    data->objects[i].b = string_to_float(split_line[2][2]);
}

void    parse_cylinder(char ***split_line, t_data *data, int i)
{
    if (line_check(split_line) != 11)
        error_exit("Wrong formatting of cylinder data");
    data->objects[i].type = cylinder;
    data->objects[i].x = string_to_float(split_line[0][0]);
    data->objects[i].y = string_to_float(split_line[0][1]);
    data->objects[i].z = string_to_float(split_line[0][2]);
    data->objects[i].vec_x = string_to_float(split_line[1][0]);
    data->objects[i].vec_y = string_to_float(split_line[1][1]);
    data->objects[i].vec_z = string_to_float(split_line[1][2]);
    data->objects[i].cyl_diameter = string_to_float(split_line[2][0]);
    data->objects[i].cyl_height = string_to_float(split_line[3][0]);
    data->objects[i].r = string_to_float(split_line[4][0]);
    data->objects[i].g = string_to_float(split_line[4][1]);
    data->objects[i].b = string_to_float(split_line[4][2]);
}
