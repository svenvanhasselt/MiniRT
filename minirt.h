/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:17:48 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/20 10:23:06 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "lib/mlx42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_color
{
    double  r;
    double  g;
    double  b;
}t_color;

typedef struct s_vec
{
    double  x;
    double  y;
    double  z;
}t_vec;

typedef struct s_ray
{
    t_vec   orig;
    t_vec   dir;
}t_ray;

typedef struct s_camera
{
    t_vec   position;
    double  ratio;
}t_camera;

typedef struct s_pixel
{
    t_ray   ray;
    uint32_t col;
    int     u;
    int     v;
}t_pixel;

void    parse_input(int argc, char **argv);
void    error_exit(void);
void    *null_check(void *check);

//yizhang
t_vec set_vec(double x, double y, double z);

//vec
t_vec	add(t_vec v1, t_vec v2);
t_vec	sub(t_vec v1, t_vec v2);
double	dot(t_vec v1, t_vec v2);
t_vec	cross(t_vec v1, t_vec v2);

//render
double hit_sphere(t_vec center, float radius, t_ray r);

#endif