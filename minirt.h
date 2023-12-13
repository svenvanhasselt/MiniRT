/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:17:48 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/13 10:10:41 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "lib/mlx42/include/MLX42/MLX42.h"
#include <stdbool.h>//bool
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define CYL_TOP 1
#define CYL_BOTTOM -1

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
	t_vec	norm;
	float	t;
	t_color	color;
}t_ray;

typedef struct s_object
{
	int		type;
	t_vec	vec;
	t_vec	vec2;
	t_ray	aixs;
	t_color	color;
	float	t;
	float	t2;
	float	sph_diameter;
	float	cyl_diameter;
	float	cyl_height;
}t_object;

typedef struct s_pixel
{
	t_ray		ray;
	uint32_t	col;
	int			u;
	int			v;
	float		t;
}t_pixel;

typedef struct s_light
{
	t_vec	point;
	t_color	color;
	float	ratio;
}t_light;

enum   t_type
{
    sphere,
    plane,
    cylinder,
};

typedef struct s_amb_light
{
    float   ambient;
    t_color color;
} t_alight;

typedef struct s_camera_s
{
    t_vec   vec;
    t_vec	ovec;
    float   fov;
	float	ratio;
	float	focal_length;
}	t_camera_s;

typedef struct s_light_s
{
	t_vec	vec;
	float	brightness;
	t_color	color;
}	t_light_s;

typedef struct s_data
{
	t_object	*objects;
	t_alight	amb_light;
	t_light_s	light;
	t_camera_s	camera;
	mlx_t		* mlx;
	mlx_image_t	*img;
	int			object_num;
	int			viewport_w;
	int			viewport_h;
	t_vec		*viewport;
	t_ray		*all_ray;
	t_pixel		*all_pix;
}   t_data;

/*  Parsing */
void	parse_input(int argc, char **argv, char ***split_file, t_data *data);
bool	line_check_data(char *line);
bool	line_check_object(char *line);
void	check_object_data(char *string,  char ***split_line, t_data *data, int obj_index);
void	error_check(int argc, char **argv);
void	replace_char(char **string, char a, char b);
void	count_objects(char *file, t_data *data);
void	free_split(char **split);
char	*input_check(char *string);
int		line_check(char ***split_line);
float	string_to_float(char *string);
void	parse_sphere(char ***split_line, t_data *data, int i);
void	parse_plane(char ***split_line, t_data *data, int i);
void	parse_cylinder(char ***split_line, t_data *data, int i);
void	parse_amb_light(char ***split_line, t_data *data);
void	parse_camera(char ***split_line, t_data *data);
void	parse_light(char ***split_line, t_data *data);

/* Errors & Checks */
void	error_exit(char *message);
void	*null_check(void *check);

//yizhang
//vec
t_vec		add(t_vec v1, t_vec v2);
t_vec		sub(t_vec v1, t_vec v2);
float		dot(t_vec v1, t_vec v2);
t_vec		cross(t_vec v1, t_vec v2);
float		vec_len(t_vec v);
t_vec		unit_vector(t_vec v);
t_vec		calc_intersection_point(t_ray r, float t);

//render && hit
bool		hit_object(t_data *data, int v);
bool		hit_sphere(t_object *obj, t_ray *r);
bool		hit_plane(t_object *obj, t_ray *ray);
float		hit_cylinder_body(t_object *obj, t_ray *ray);
float		hit_cylinder_caps(t_object *obj, t_ray *ray);
float		compare_t(float t, float t2);
bool		hit_cylinder(t_object *obj, t_ray *ray);
t_color		ray_color(t_ray ray, float t, t_object object, t_data *data);
t_vec		set_facenorm(t_vec ray_dir, t_vec face);
t_vec		set_vec(float x, float y, float z);
t_color		set_col(float r, float g, float b);
t_ray		set_ray(t_vec orig, t_vec dir);
t_pixel		set_pixel(t_ray ray, int u, int v, uint32_t col);

//color
uint32_t	get_rgba(float r, float g, float b, float a);
float		clamp(float value, float min, float max);

void		give_color(t_data *data, int weith, int high, int v);
void		init_pix(t_data *data);
void		print_pix(t_data *data);
#endif