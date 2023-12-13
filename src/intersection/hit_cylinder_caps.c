/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder_caps.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 08:10:22 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/13 16:58:06 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../minirt.h"

//ray-Disk Intersection
//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html

static float hit_onedisc(t_vec top_bottom, t_ray *ray, t_object *obj)
{
	t_vec oc;
	float t;
	float d;
	t_vec p;
	t = -1;
	oc = sub(ray->orig, top_bottom);
	t = -dot(oc,obj->vec2) / dot(ray->dir,obj->vec2);
	if (t > 0)
	{
		p = calc_intersection_point(*ray, t);
		oc = sub(p, top_bottom);
		d = dot(oc,oc);
		if (sqrt(d) <= obj->cyl_diameter/2)
			return (t);
	}
	return (-1);
	}

static t_vec top_bottom(t_object *obj, int top_bottom)
{
	float	x;
	float	y;
	float	z;

	x = 0.0;
	y = 0.0;
	z = 0.0;
	if (top_bottom == CYL_TOP)
	{
		x = obj->vec.x + obj->vec2.x * obj->cyl_height / 2;
		y = obj->vec.y + obj->vec2.y * obj->cyl_height / 2;
		z = obj->vec.z + obj->vec2.z * obj->cyl_height / 2;
		return(set_vec(x,y,z));
	}
	else if (top_bottom == CYL_BOTTOM)
	{
		x = obj->vec.x - obj->vec2.x * obj->cyl_height / 2;
		y = obj->vec.y - obj->vec2.y * obj->cyl_height / 2;
		z = obj->vec.z - obj->vec2.z * obj->cyl_height / 2;
	}
	return(set_vec(x,y,z));
	}

float hit_cylinder_caps(t_object *obj, t_ray *ray)
{
	float	t;
	float	t2;

	obj->cyl_top = top_bottom(obj, CYL_TOP);
	obj->cyl_bottom = top_bottom(obj, CYL_BOTTOM);
	t = hit_onedisc(obj->cyl_bottom,ray,obj);
	t2 = hit_onedisc(obj->cyl_top,ray,obj);
	return (compare_t(t, t2));
}

