/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_plane.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 09:24:28 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/13 16:59:02 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

/*
	(D*t+X)|V = 0
	D|V*t = -X|V
	t = -X|V / D|V
	https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
 */
bool	hit_plane(t_object *obj, t_ray *ray)
{
	t_vec	oc;
	
	oc = sub(ray->orig, obj->vec);
	obj->t = -dot(oc,obj->vec2)/ dot(ray->dir,obj->vec2);

	if (obj->t < 0)
		return (false);
	return (true);
}
