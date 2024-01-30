/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_plane.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 09:24:28 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/30 17:13:44 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	hit_plane(t_object *obj, t_ray *ray)
{
	t_vec	oc;


	// float	len;
	// t_vec	hitpoint;

	// t_vec oc = sub(ray->orig, ray->obj->vec);
	// if (ray->obj->type == plane)
	// 	ray->t = -dot(oc, ray.obj->vec2) / dot(ray.dir, ray.obj->vec2);
	// printf("t: %f\n", ray.t);
	
	oc = sub(ray->orig, obj->vec);
	obj->t = -dot(oc, obj->vec2) / dot(ray->dir, obj->vec2);
	// hitpoint = calc_hitpoint(*ray, ray->t);
	// len = vec_len(sub(hitpoint, ray->orig));
	// printf("len: %f\n", len);
	if (obj->t >= 0)
		return (true);
	return (false);
}
