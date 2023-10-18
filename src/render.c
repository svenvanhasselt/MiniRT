/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 17:47:22 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/18 13:33:11 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double hit_sphere(t_vec center, float radius, t_ray r) 
{
	t_vec oc = sub(r.orig, center);
	double a = dot(r.dir, r.dir);
	double b = 2.0 * dot(oc, r.dir);
	double c = dot(oc, oc) - radius*radius;
	double discriminant = b*b - 4*a*c;
    return (discriminant);
}