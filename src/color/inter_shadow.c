/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:28:57 by svan-has          #+#    #+#             */
/*   Updated: 2024/02/10 16:41:56 by sven             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	check_max_len(t_ray *ray, t_data *data)
{
	float	len;
	float	max_len;
	t_vec	hitpoint;

	hitpoint = calc_hitpoint(*ray, ray->t);
	len = vec_len(sub(hitpoint, ray->orig));
	max_len = vec_len(sub(data->light.vec, ray->orig));
	if (len >= max_len)
		return (false);
	return (true);
}

bool	hit_plane2(t_object *obj, t_ray *ray, t_data *data)
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
	if (!check_max_len(ray, data))
		return (false);
	if (obj->t >= 0)
		return (true);
	return (false);
}
