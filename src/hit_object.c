/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_object.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 13:43:59 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/26 14:51:38 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


//make a object list
bool    hit_object(t_obj obj)
{
	float	t;
	t = -1;
	//sphere
	t = hit_sphere(t_vec center, float radius, t_ray r);
	//cyl
	//etc
	if (t > 0)
		return (true);
	else
		return (false);
}