/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_plane.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 09:24:28 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/01 11:06:49 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

/* 
plane equation is :p*n -d = 0
ray: p(t) = s + tc;
intersection : (s +tc) * n -d = 0
t = (d - s*n)/c*n
 */
bool	hit_plane(t_object *obj, t_ray *ray)
{
	float   ortho;
    float   d;
    float   dis;
    
    ortho = dot(obj->vec2, ray->norm);
    if (ortho == 0)
        return (false);
    d = dot(obj->vec, obj->vec2);
    dis = dot(obj->vec2, ray->orig);
    obj->t = (d - dis) / ortho;
	return (true);
}
