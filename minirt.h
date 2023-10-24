/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:17:48 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/24 17:47:30 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "lib/mlx42/include/MLX42/MLX42.h"
#include <stdio.h>

enum   t_type
{
    sphere,
    plane,
    cylinder,
};

typedef struct s_object
{
    int     type;
    float   x;
    float   y;
    float   z;
    float   sph_diameter;
    float    r;
    float    g;
    float    b;
    float   vec_x;
    float   vec_y;
    float   vec_z;
    float   cyl_diameter;
    float   cyl_height;
}   t_object;

typedef struct s_amb_light
{
    float   ambient;
    int     r;
    int     g;
    int     b;
} t_alight;

typedef struct s_camera
{
    float   x;
    float   y;
    float   z;
    float   ov_x;
    float   ov_y;
    float   ov_z;
    float   fov;
}   t_camera;

typedef struct s_light
{
    float   x;
    float   y;
    float   z;
    float   brightness;
    float   r;
    float   g;
    float   b;
} t_light;

typedef struct s_data
{
    t_object    *objects;
    t_alight    amb_light;
    t_light     light;
    t_camera    camera;
    int         object_num;
}   t_data;

/*  Parsing */
void    parse_input(int argc, char **argv, char ***split_file, t_data *data);
bool    line_check_data(char *line);
bool    line_check_object(char *line);
void    replace_char(char **string, char a, char b);
void    count_objects(char *file, t_data *data);
void    free_split(char **split);
char    *input_check(char *string);
int     line_check(char ***split_line);
float   string_to_float(char *string);
void    parse_sphere(char ***split_line, t_data *data, int i);
void    parse_plane(char ***split_line, t_data *data, int i);
void    parse_cylinder(char ***split_line, t_data *data, int i);
void    parse_amb_light(char ***split_line, t_data *data);
void    parse_camera(char ***split_line, t_data *data);
void    parse_light(char ***split_line, t_data *data);

/* Errors & Checks */
void    error_exit(char *message);
void    *null_check(void *check);

#endif