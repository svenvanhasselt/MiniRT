/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setter.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/23 15:43:33 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/30 15:23:38 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_vec	set_vec(float x, float y, float z)
{
	t_vec	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_ray	set_ray(t_vec orig, t_vec dir)
{
	t_ray	new;

	new.orig = orig;
	new.dir = dir;
	new.norm = unit_vector(sub(orig, dir));
	return (new);
}

t_pixel	set_pixel(t_ray ray, int u, int v, uint32_t col)
{
	t_pixel	new;

	new.ray = ray;
	new.u = u;
	new.v = v;
	new.col = col;
	return (new);
}
