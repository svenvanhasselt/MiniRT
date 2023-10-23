/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:17:48 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/23 16:37:46 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "lib/mlx42/include/MLX42/MLX42.h"
#include <stdio.h>

enum   t_type
{
    sphere,
    cilinder,
};

typedef struct s_object
{
    int     type;
    float   x;
    float   y;
    float   z;
    float   diameter;
    int     r;
    int     g;
    int     b;
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
    int     fov;
}   t_camera;

typedef struct s_light
{
    float   x;
    float   y;
    float   z;
    float   bright_a;
    float   bright_b;
    float   bright_c;
} t_light;

typedef struct s_data
{
    t_object    *objects;
    t_alight    *amb_light;
    t_light     *light;
    t_camera    *camera;
    int         object_num;
}   t_data;

/*  Parsing */
void    parse_input(int argc, char **argv, char ***split_file, t_data *data);
bool    line_check_data(char *line);
bool    line_check_object(char *line);
void    replace_char(char **string, char a, char b);
void    count_objects(char *file, t_data *data);
void    free_split(char **split);
void    parse_sphere(char ***split_line, t_data *data, int i);
char    *input_check(char *string);

/* Errors & Checks */
void    error_exit(void);
void    *null_check(void *check);

#endif