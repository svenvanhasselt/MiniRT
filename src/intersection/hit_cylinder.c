// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   hit_cylinder.c                                     :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: sven <sven@student.42.fr>                    +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/11/27 16:47:30 by yizhang       #+#    #+#                 */
// /*   Updated: 2024/02/02 17:28:22 by svan-has      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../minirt.h"

// float	hit_cylinder_body(t_object *obj, t_ray *ray)
// {
// 	t_vec	oc;

// 	oc = sub(ray->orig, obj->vec);
// 	obj->discrim.a = dot(ray->dir, ray->dir)
// 		- pow(dot(ray->dir, obj->vec2), 2);
// 	obj->discrim.b = 2 * (dot(ray->dir, oc)
// 			- dot(ray->dir, obj->vec2) * dot(oc, obj->vec2));
// 	obj->discrim.c = dot(oc, oc)
// 		- pow(dot(oc, obj->vec2), 2)
// 		- pow(obj->diameter / 2, 2);
// 	obj->discrim.d = discriminant(obj->discrim.a,
// 			obj->discrim.b, obj->discrim.c);
// 	calculate_t_and_m(obj, ray);
// 	return (obj->t);
// }

void	calculate_t(t_object *obj, t_ray *ray)
{
	float	max;
	t_vec	hitpoint;

	max = sqrt(pow(obj->height / 2, 2) + pow(obj->diameter, 2));
	obj->t = (-obj->discrim.b - sqrt(obj->discrim.d)) / (obj->discrim.a * 2);
	obj->t2 = (-obj->discrim.b + sqrt(obj->discrim.d)) / (obj->discrim.a * 2);
	if (obj->t2 <= 0.0001 && obj->t <= 0.0001)
		return ;
	if (obj->t <= 0.0001 || (obj->t2 > 0.0001 && (obj->t2 < obj->t)))
		obj->t = obj->t2;
	hitpoint = calc_hitpoint(*ray, obj->t);
	if (vec_len(sub(hitpoint, obj->vec)) > max)
	{
		obj->t = obj->t2;
		obj->inside = true;
	}
	hitpoint = calc_hitpoint(*ray, obj->t);
	if (vec_len(sub(hitpoint, obj->vec)) < max)
		return ;
	else
		obj->t = -1;
}


float	hit_cylinder_body(t_object *obj, t_ray *ray)
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

bool	hit_cylinder(t_object *obj, t_ray *ray)
{
	float	t;
	float	t2;

	t = hit_cylinder_caps(obj, ray);
	t2 = hit_cylinder_body(obj, ray);
	obj->t = t2;
	if (obj->t > 0)
		return (true);
	return (false);
}