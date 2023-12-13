/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 09:10:52 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/13 16:59:46 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

// This function is to compare which t is closer to the camera

/* static void	swap_t(float *t, float *t2)
{
	float	tmp;

	tmp = *t;
	*t = *t2;
	*t2 = tmp;
} */

float	compare_t(float t, float t2)//the first t will have the correct value
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

void	update_obj(t_ray *ray, t_object *obj)
{
	float	t;

	t = compare_t(ray->t, obj->t);
	if (t == obj->t)
		ray->obj = obj;
	else if (t == ray->t || t == -1)
		return ;
}