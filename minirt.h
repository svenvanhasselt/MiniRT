/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:17:48 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/16 15:55:15 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "lib/mlx42/include/MLX42/MLX42.h"
#include <stdbool.h>//bool
#include <stdlib.h>
#include <math.h>
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
void    check_object_data(char *string,  char ***split_line, t_data *data, int obj_index);
void    error_check(int argc, char **argv);
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
	float	r;
	float	g;
	float	b;
}t_color;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}t_vec;

typedef struct s_ray
{
	t_vec	orig;
	t_vec	dir;
}t_ray;

typedef struct s_camera
{
	t_vec	position;
	float	ratio;
}t_camera;

typedef struct s_obj
{
	int		type;
	t_vec	center;
	t_color	color;
	t_vec	norm;
	float	vec_x;
	float	vec_y;
	float	vec_z;
	float	sph_diameter;
	float	cyl_diameter;
	float	cyl_height;
	struct	s_obj	*next;
}t_obj;

typedef struct s_pixel
{
	t_ray		ray;
	uint32_t	col;
	int			u;
	int			v;
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
t_vec		t_to_vec(float disc, t_ray ray);

//render && hit
bool		hit_object(t_ray ray, t_obj *obj);
float		hit_sphere(t_vec center, float radius, t_ray r);
t_color		ray_color(t_ray r, float t, t_vec oc);
t_vec		set_facenorm(t_vec ray_dir, t_vec face);

//color
uint32_t	get_rgba(int r, int g, int b, int a);

#endif