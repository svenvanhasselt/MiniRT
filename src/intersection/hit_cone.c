/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cone.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 10:25:21 by yizhang       #+#    #+#                 */
/*   Updated: 2024/02/01 17:14:29 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	hit_cone(t_object *obj, t_ray *ray)
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
