/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:17:48 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/26 14:52:19 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "lib/mlx42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>//bool

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
    float  r;
    float  g;
    float  b;
}t_color;

typedef struct s_vec
{
    float  x;
    float  y;
    float  z;
}t_vec;

typedef struct s_ray
{
    t_vec   orig;
    t_vec   dir;
}t_ray;

typedef struct s_camera
{
    t_vec   position;
    float  ratio;
}t_camera;

typedef struct s_obj
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
}   t_obj;

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
	float	ratio;
}t_light;

void		parse_input(int argc, char **argv);
void		error_exit(void);
void		*null_check(void *check);

//yizhang
t_vec		set_vec(float x, float y, float z);
t_color		set_col(float r, float g, float b);

//vec
t_vec		add(t_vec v1, t_vec v2);
t_vec		sub(t_vec v1, t_vec v2);
float		dot(t_vec v1, t_vec v2);
t_vec		cross(t_vec v1, t_vec v2);
float		vec_len(t_vec v);
t_vec		unit_vector(t_vec v);

//render
float		hit_sphere(t_vec center, float radius, t_ray r);
t_vec		t_to_vec(float disc, t_ray ray);
t_color		ray_color(t_ray r, float t);

//color
uint32_t	get_rgba(int r, int g, int b, int a);

#endif