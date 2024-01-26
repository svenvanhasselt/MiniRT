/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:17:48 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/26 15:37:28 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "lib/mlx42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define CYL_TOP 1
# define CYL_BOTTOM -1

typedef struct s_data	t_data;

enum	e_type
{
	none,
	sphere,
	plane,
	cylinder,
	cone,
};

enum	e_action
{
	translate,
	rotate,
};

enum	e_object_type
{
	camera,
	light,
	object,
};

enum	e_axis
{
	x_axis,
	y_axis,
	z_axis,
};

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_quat
{
	float	a;
	float	b;
	float	c;
	float	d;
}	t_quat;

typedef struct s_ray
{
	t_vec			orig;
	t_vec			dir;
	t_vec			norm;
	float			t;
	t_vec			color;
	struct s_object	*obj;
	bool			inside;
}	t_ray;

typedef struct s_object
{
	int		id;
	int		type;
	t_vec	vec;
	t_vec	vec2;
	t_ray	aixs;
	t_vec	color;
	t_quat	discrim;
	float	t;
	float	t2;
	float	m1;
	float	m2;
	float	diameter;
	float	height;
	float	angle;
	float	k;
}	t_object;

typedef struct s_pixel
{
	t_ray		ray;
	uint32_t	col;
	int			u;
	int			v;
}	t_pixel;

typedef struct s_amb_light
{
	float	ambient;
	t_vec	color;
}	t_alight;

typedef struct s_camera
{
	t_vec	vec;
	t_vec	ovec;
	t_vec	right;
	t_vec	up;
	float	fov;
	float	focal_length;
}	t_camera;

typedef struct s_light
{
	t_vec	vec;
	float	brightness;
	t_vec	color;
}	t_light;

typedef struct s_rotation
{
	int			obj_type;
	t_object	*object;
	void		(*action)(t_data *data, int axis, float value);
}	t_rotation;

typedef struct s_data
{
	t_object	*objects;
	t_alight	amb_light;
	t_light		light;
	t_camera	camera;
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			object_num;
	int			viewport_w;
	int			viewport_h;
	int			ray_pix_num;
	t_vec		*viewport;
	t_ray		*all_ray;
	t_pixel		*all_pix;
	t_rotation	rotation;
}	t_data;

/*  Parsing */
void		parse_input(int argc, char **argv, char ***split_file, \
t_data *data);
float		check_v(float value, float min, float max);
bool		line_check_data(char *line);
bool		line_check_object(char *line);
void		check_object_data(char *string, char ***split_line, \
t_data *data, int obj_index);
void		error_check(int argc, char **argv, int *rt_file);
void		replace_char(char **string, char a, char b);
void		count_objects(t_data *data, int rt_file);
void		free_split(char **split);
char		*input_check(char *string);
int			line_check(char ***split_line);
void		parse_sphere(char ***split_line, t_data *data, int i);
void		parse_plane(char ***split_line, t_data *data, int i);
void		parse_cylinder(char ***split_line, t_data *data, int i);
void		parse_cone(char ***split_line, t_data *data, int i);
void		parse_resolution(char ***split_line, t_data *data);
void		parse_amb_light(char ***split_line, t_data *data);
void		parse_camera(char ***split_line, t_data *data);
void		parse_light(char ***split_line, t_data *data);

/* Vector */
t_vec		add(t_vec v1, t_vec v2);
t_vec		sub(t_vec v1, t_vec v2);
float		dot(t_vec v1, t_vec v2);
t_vec		cross(t_vec v1, t_vec v2);
float		vec_len(t_vec v);
t_vec		unit_vector(t_vec v);
t_vec		calc_intersection_point(t_ray r, float t);
t_vec		mult_fact(t_vec vec, float fact);
t_vec		mult(t_vec v1, t_vec v2);

/* Render & Hit */
bool		hit_object(t_data *data, int v);
bool		hit_sphere(t_object *obj, t_ray *r);
bool		hit_plane(t_object *obj, t_ray *ray);
bool		hit_cone(t_object *obj, t_ray *ray);
float		hit_cylinder_body(t_object *obj, t_ray *ray);
float		hit_cylinder_caps(t_object *obj, t_ray *ray);
bool		calculate_t_and_m(t_object *obj, t_ray *ray);
float		discriminant(float a, float b, float c);
void		compare_update_t(t_object *obj, t_ray *ray);
float		compare_t(float t, float t2);
bool		hit_cylinder(t_object *obj, t_ray *ray);
t_vec		ray_color(t_ray ray, float t, t_object *object, t_data *data);
t_vec		set_facenorm(t_vec ray_dir, t_vec face);
t_vec		set_vec(float x, float y, float z);
t_ray		set_ray(t_vec orig, t_vec dir);
t_pixel		set_pixel(t_ray ray, int u, int v, uint32_t col);
void		calc_viewport(t_data *data);

/* Color & Shade */
uint32_t	get_rgba(float r, float g, float b);
float		clamp(float value, float min, float max);
t_vec		calc_surface_normal(t_vec intersection_point, t_vec oc);
float		calc_diffuse(t_vec light_pos, t_vec surf_norm, \
t_vec inter_point, float brightness);
t_vec		calc_ambient(t_data *data, t_object *object);
t_vec		norm_sphere(t_ray ray, t_object *object, t_vec hit_point);
t_vec		norm_cylinder(t_ray ray, t_object *object, t_vec hit_point);
t_vec		norm_cone(t_ray ray, t_object *object, t_vec hit_point);
t_vec		norm_plane(t_ray ray, t_object *object);

/* Rotation & Translation */
void		init_rotation(t_data *data);
t_vec		init_camera(t_data *data, float j, float i);
t_vec		rotate_vector(t_vec vec, t_quat r);
void		rotation(t_data *data, int axis, float value);
void		translation(t_data *data, int axis, float value);
void		change_type(t_data *data, int type, t_object *obj);
void		key_press(mlx_key_data_t kd, void *param);
void		init_pix(t_data *data);
void		print_pix(t_data *data);
t_quat		set_quat(float a, float b, float c, float d);
void		reset_pix(t_data *data);
t_quat		unit_quat(t_quat q);

// Tools
void		print_message(t_data *data, char *message);
void		moving_keys(mlx_key_data_t kd, t_data *data);
void		control_keys(mlx_key_data_t kd, t_data *data);
void		key_press(mlx_key_data_t kd, void *param);
void		error_exit(char *message);
void		*null_check(void *check);

#endif