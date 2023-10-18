/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:17:48 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/18 10:02:14 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "lib/mlx42/include/MLX42/MLX42.h"
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

void    parse_input(int argc, char **argv);
void    error_exit(void);
void    *null_check(void *check);

//yizhang
t_vec set_vec(double x, double y, double z);

#endif