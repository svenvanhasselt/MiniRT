/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:24:28 by yizhang           #+#    #+#             */
/*   Updated: 2024/02/10 15:42:45 by sven             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	hit_plane(t_object *obj, t_ray *ray)
{
	float	denom;
	t_vec	oc;

	oc = sub(ray->orig, obj->vec);
	denom = dot(obj->vec2, ray->dir);
	if (denom == 0)
		return (false);
	obj->t = -dot(oc, obj->vec2) / denom;
	if (obj->t < 0.0001)
		return (false);
	if (dot(obj->vec2, ray->dir) > 0)
		obj->inside = true;
	else
		obj->inside = false;
	return (true);
}
