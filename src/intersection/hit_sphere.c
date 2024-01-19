/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_sphere.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 09:24:23 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/19 14:22:41 by yizhang       ########   odam.nl         */
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
	obj->discrim.d = obj->discrim.b * obj->discrim.b - 4
		* obj->discrim.a * obj->discrim.c;
	obj->t = (-obj->discrim.b / 2 - sqrt(obj->discrim.d)) / obj->discrim.a;
	if (obj->discrim.d < 0)
		return (false);
	if (obj->t >= 0)
		return (true);
	return (false);
}
