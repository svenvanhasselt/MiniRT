/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setter.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/23 15:43:33 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/27 16:14:55 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minirt.h"

t_vec set_vec(float x, float y, float z)
{
	t_vec new;
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);	
}

t_color set_col(float r, float g, float b)
{
	t_color new;
	new.r = r;
	new.g = g;
	new.b = b;
	return (new);	
}

t_ray set_ray(t_vec orig, t_vec dir)
{
	t_ray new;
	new.orig = orig;
	new.dir = dir;
	new.norm = unit_vector(sub(orig,dir));
	return (new);
}

t_pixel set_pixel(t_ray ray, int u, int v, uint32_t col)
{
	t_pixel new;
	new.ray = ray;
	new.u = u;
	new.v = v;
	new.col = col;
	return(new);
}
