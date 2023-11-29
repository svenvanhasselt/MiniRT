/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_plane.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 09:24:28 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/29 16:13:53 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

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
