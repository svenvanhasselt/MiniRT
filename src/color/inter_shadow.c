/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inter_shadow.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 17:28:57 by svan-has      #+#    #+#                 */
/*   Updated: 2024/02/08 18:27:18 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	hit_cone2(t_object *obj, t_ray *ray)
{
	float	tana;
	t_vec	oc;

	obj->t = -1;
	obj->t2 = -1;
	oc = sub(ray->orig, obj->vec);
	tana = tan(45.0 / 180.0 * 3.141);
	obj->discrim.a = dot(ray->dir, ray->dir)
		- (1 + tana * tana) * pow(dot(ray->dir, obj->vec2), 2);
	obj->discrim.b = 2 * (dot(ray->dir, oc)
			- (1 + tana * tana) * dot(ray->dir, obj->vec2)
			* dot(oc, obj->vec2));
	obj->discrim.c = dot(oc, oc)
		- (1 + tana * tana) * pow(dot(oc, obj->vec2), 2);
	obj->discrim.d = obj->discrim.b * obj->discrim.b - 4
		* obj->discrim.a * obj->discrim.c;
	return (calculate_t_and_m(obj, ray));
}



float	hit_cylinder_body2(t_object *obj, t_ray *ray, int id)
{
	t_vec		u;
	t_vec		v;
	float		r2;


	obj->inside = false;
	r2 = obj->diameter * obj->diameter * 0.25;
	u = cross(ray->dir, obj->vec2);
	v = sub(ray->orig, obj->vec);
	v = cross(v, obj->vec2);
	obj->discrim.a = dot(u, u);
	obj->discrim.b = 2 * dot(u, v);
	obj->discrim.c = dot(v, v) - r2;
	obj->discrim.d = discriminant(obj->discrim.a, obj->discrim.b, obj->discrim.c);
	if (obj->discrim.d < 0)
		return (-1);
	calculate_t(obj, ray);
	return (obj->t);
}

bool	hit_cylinder2(t_object *obj, t_ray *ray, int id)
{
	float	t;

	t = hit_cylinder_body2(obj, ray, id);
	if (obj->t > 0)
		return (true);
	return (false);
}

bool	hit_sphere2(t_object *obj, t_ray *ray, t_data *data)
{
	float	radius;
	t_vec	oc;
	t_vec	hitpoint;
	float	len;
	float	max_len;

	radius = obj->diameter / 2;
	oc = sub(ray->orig, obj->vec);
	obj->discrim.a = dot(ray->dir, ray->dir);
	obj->discrim.b = 2.0 * dot(oc, ray->dir);
	obj->discrim.c = dot(oc, oc) - radius * radius;
	obj->discrim.d = discriminant(obj->discrim.a,
			obj->discrim.b, obj->discrim.c);
	obj->t = (-obj->discrim.b - sqrt(obj->discrim.d)) / (2 * obj->discrim.a);
	hitpoint = calc_hitpoint(*ray, ray->t);
	len = vec_len(sub(ray->orig, hitpoint));
	max_len = vec_len(sub(ray->orig, data->light.vec));
	if (len < max_len)
		return (false);
	if (obj->discrim.d < 0)
		return (false);
	if (obj->t >= 0)
		return (true);
	return (false);
}

// bool	hit_plane2(t_object *obj, t_ray *ray, t_data *data)
// {
// 	t_vec	oc;
// 	t_vec	hitpoint;
// 	float	len;
// 	float	max_len;
	
// 	oc = sub(ray->orig, obj->vec);
// 	obj->t = -dot(oc, obj->vec2) / dot(ray->dir, obj->vec2);
// 	if (dot(ray->dir, obj->vec2) > 0)
// 		obj->inside = true;
// 	else
// 		obj->inside = false;
// 	hitpoint = calc_hitpoint(*ray, ray->t);
// 	hitpoint = unit_vector(hitpoint);
// 	len = vec_len(sub(hitpoint, ray->orig));
// 	max_len = vec_len(sub(data->light.vec, ray->orig));
// 	// printf("maxlen %f len %f\n", max_len, len);
// 	// if (len > 500 || max_len > 500)
// 	// 	return (true);
// 	if (len >= max_len)
// 		return (false);
// 	if (obj->t >= 0)
// 		return (true);
// 	return (false);
// }

bool	hit_plane2(t_object *obj, t_ray *ray, t_data *data)
{
	t_vec	oc;
	t_vec	hitpoint;
	float	len;
	float	max_len;
	
	oc = sub(ray->orig, obj->vec);
	float denom = dot(obj->vec2, ray->dir);
	if (denom == 0)
		return (false);
	obj->t = -dot(oc, obj->vec2) / denom;
	if (obj->t < 0.0001)
		return (false);
	hitpoint = calc_hitpoint(*ray, ray->t);
	hitpoint = unit_vector(hitpoint);
	len = vec_len(sub(hitpoint, ray->orig));
	max_len = vec_len(sub(data->light.vec, ray->orig));
	if (len >= max_len)
		return (false);
	if (obj->t >= 0)
		return (true);
	return (false);
}
