/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_caps.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 18:15:55 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/11 18:25:19 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//ray-Disk Intersection
//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
bool    hit_cylinder_caps(t_object *obj, t_ray *ray)
{
    t_vec	top;
    t_vec   bottom;
    float   x;
    float   y;
    float   z;
    t_vec	oc;
    float   t;
    float   t2;

    x = obj->vec.x + obj->vec2.x * obj->cyl_height / 2;
    y = obj->vec.y + obj->vec2.y * obj->cyl_height / 2;
    z = obj->vec.z + obj->vec2.z * obj->cyl_height / 2;
    top = set_vec(x,y,z);

    x = obj->vec.x - obj->vec2.x * obj->cyl_height / 2;
    y = obj->vec.y - obj->vec2.y * obj->cyl_height / 2;
    z = obj->vec.z - obj->vec2.z * obj->cyl_height / 2;
    top = set_vec(x,y,z);
	
    // printf("center: x:%f y:%f z:%f\n", obj->vec.x,obj->vec.y,obj->vec.z);
    // printf("top: x:%f y:%f z:%f\n", x,y,z);
	
    t = hit_onedisc(bottom,ray,obj);
    t2 = hit_onedisc(top,ray,obj);
    
    if (t >= 0 && t2 >= 0)
	{
		if (t > t2)
			obj->t = t;
	}
	if (obj->t < 0)
		obj->t = t;
}

float hit_onedisc(t_vec top_bottom, t_ray *ray, t_object *obj)
{
    t_vec oc;
    float t;
    
    t = 0;
    oc = sub(ray->orig, top_bottom);
	t = -dot(oc,obj->vec2)/ dot(ray->dir,obj->vec2);
    if (t > 0)
    {
        t_vec p = calc_intersection_point(*ray, t);
        oc = sub(p, top_bottom);
        float d = dot(oc,oc);
        if (sqrt(d) <= obj->cyl_diameter/2)
        {
            return (t);
        }
    }
    return (-1);
}