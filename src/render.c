/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 17:47:22 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/30 10:15:29 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>

t_color ray_color(t_ray r, float t, t_vec oc)
{
	//if (t > 0.0)
	//{					//the close point on the sphere, and the center of sphere
		t_vec n = unit_vector(sub(t_to_vec(t, r), oc));
		return set_col(0.5 * (n.x + 1), 0.5 * (n.y + 1), 0.5 * (n.z + 1));//color range base on the unit_vector
	//}
	//t_vec unit_direction = unit_vector(r.dir);
	//float  a = 0.5 * (unit_direction.y + 1.0);
	//return (set_col((1.0 - a) + a * 0.5, (1.0 - a) + a * 0.7, (1.0 - a) + a * 1.0));
}
