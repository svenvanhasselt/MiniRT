/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_sphere.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 09:24:23 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/19 13:48:38 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool hit_sphere(t_object *obj, t_ray *r) 
{
	float	radius;

	radius = obj->diameter / 2;
	t_vec oc = sub(r->orig, obj->vec);
	float a = dot(r->dir, r->dir);
	float b = 2.0 * dot(oc, r->dir);
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4*a*c;
	obj->t = (-b/2 -sqrt(discriminant)) / a;
	if (discriminant < 0)
		return (false);
	if (obj->t >= 0)
		return (true);
	return (false);
}