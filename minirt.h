/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:17:48 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/24 16:45:12 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "lib/mlx42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>//for sqrt()

#define MINT 0.2
#define MAXT 40//dont know how to define

typedef enum e_num
{
	sphere,
	plane,
	cylinder,
}t_enum;

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

/* typedef struct s_object
{
	int		type;
	t_vec	center;
	t_color	color;
	double	r;
}t_object;
 */
typedef struct s_pixel
{
    t_ray   ray;
    uint32_t col;
    int     u;
    int     v;
}t_pixel;

typedef struct s_light
{
	t_vec	point;
	t_color	color;
	double	ratio;
}t_light;

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
//color
uint32_t get_rgba(int r, int g, int b, int a);

#endif