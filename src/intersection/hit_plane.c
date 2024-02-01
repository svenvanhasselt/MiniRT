/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_plane.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 09:24:28 by yizhang       #+#    #+#                 */
/*   Updated: 2024/02/01 16:48:28 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	hit_plane(t_object *obj, t_ray *ray)
{
	t_vec	oc;


	oc = sub(ray->orig, obj->vec);
	obj->t = -dot(oc, obj->vec2) / dot(ray->dir, obj->vec2);

	
	if (dot(ray->dir, obj->vec2) > 0)
		obj->inside = true;
	else
		obj->inside = false;
	if (obj->t >= 0)
		return (true);
	return (false);
}
