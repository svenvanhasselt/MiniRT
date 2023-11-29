/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 12:57:37 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/29 15:30:05 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>

t_vec	add(t_vec v1, t_vec v2)
{
	t_vec new;
	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	new.z = v1.z + v2.z;
	return (new);
}

t_vec	sub(t_vec v1, t_vec v2)
{
	t_vec new;
	new.x = v1.x - v2.x;
	new.y = v1.y - v2.y;
	new.z = v1.z - v2.z;
	return (new);
}

float	dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	cross(t_vec v1, t_vec v2)
{
	t_vec new;
	new.x = v1.y * v2.z - v1.z * v2.y;
	new.y = v1.z * v2.x - v1.x * v2.z;
	new.z = v1.x * v2.y - v1.y * v2.x;
	return (new);
}

float vec_len(t_vec v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec unit_vector(t_vec v)
{
    float len;
	len = vec_len(v);
    t_vec ret;
	ret = set_vec(v.x / len, v.y / len, v.z / len);
    return ret;
}

//Find Intersection Point vector:
//t value, plug it back into the ray equation to find the intersection point:
//	P = O + t*D
//P:intersection
//O:origin
//D:deriction
//reverse inference to derive value

t_vec	calc_intersection_point(t_ray r, float t)
{
	t_vec	intersection_point;

	intersection_point.x = r.orig.x + t * r.dir.x;
	intersection_point.y = r.orig.y + t * r.dir.y;
	intersection_point.z = r.orig.z + t * r.dir.z;
	return (intersection_point);
}