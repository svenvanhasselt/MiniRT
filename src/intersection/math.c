/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 09:10:52 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/19 13:52:58 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

float	compare_t(float t, float t2)
{
	if (t < 0 && t2 >= 0)
		return (t2);
	else if (t2 < 0 && t >= 0)
		return (t);
	else if (t >= 0 && t2 >= 0)
	{
		if (t < t2)
			return (t);
		else
			return (t2);
	}
	return (-1);
}

void	compare_update_t(t_object *obj, t_ray *ray)
{
	ray->t = compare_t(obj->t, ray->t);
	if (ray->t == obj->t && ray->t >= 0)
		ray->obj = obj;
}
