/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_sphere.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 09:24:23 by yizhang       #+#    #+#                 */
/*   Updated: 2024/02/08 18:20:04 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	hit_sphere(t_object *obj, t_ray *r)
{
	float	radius;
	t_vec	oc;

	radius = obj->diameter / 2;
	oc = sub(r->orig, obj->vec);
	obj->discrim.a = dot(r->dir, r->dir);
	obj->discrim.b = 2.0 * dot(oc, r->dir);
	obj->discrim.c = dot(oc, oc) - radius * radius;
	obj->discrim.d = discriminant(obj->discrim.a,
			obj->discrim.b, obj->discrim.c);
	if (obj->discrim.d < 0)
		return (false);
	obj->t = (-obj->discrim.b - sqrt(obj->discrim.d)) / (2 * obj->discrim.a);
	obj->t2 = (-obj->discrim.b + sqrt(obj->discrim.d)) / (2 * obj->discrim.a);
	obj->t = compare_t(obj->t, obj->t2);
	if (obj->t >= 0)
		return (true);
	return (false);
}
