/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 16:47:30 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/11 18:17:52 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

//x2 + y2 = r2;
//ray = p + tv;

//this is a basic cylinder
    // a = pow(ray->dir.x, 2) + pow(ray->dir.z, 2);
    // b = 2 * (ray->dir.x * ray->orig.x + ray->dir.z * ray->orig.z);
    // c = pow(ray->orig.x, 2) + pow(ray->orig.z, 2) - pow(obj->cyl_diameter/2, 2);
    
/* a = D|D - (D|V)^2

c = X|X - (X|V)^2 - r^2

b = 2 * (D-V*(D|V))|(X-V*(X|V)) =
 = 2 * (D|X - D|V*(X|V) - X|V*(D|V) + (D|V)*(X|V)) =
 = 2 * (D|X - (D|V)*(X|V)) */

//https://stackoverflow.com/questions/73866852/ray-cylinder-intersection-formula

bool	hit_cylinder_body(t_object *obj, t_ray *ray)
{
	float   a;
    float   b;
    float   c;
    float   discriminant;
    float   r;
    t_vec   oc;
   
    r = obj->cyl_diameter/2;
    
    oc = sub(ray->orig,obj->vec);//subtract the center of the cylinder from the ray origin to turn the problem into a (0,0,0) coordinate
    a = dot(ray->dir,ray->dir) - pow(dot(ray->dir, obj->vec2),2);
    b = 2*(dot(ray->dir, oc) - dot(ray->dir, obj->vec2) * dot(oc, obj->vec2));
    c = dot(oc, oc) - pow(dot(oc, obj->vec2), 2) - pow(r / 2, 2);
    
    //Calculate the discriminant
    discriminant = b*b - 4*a*c;
    if (discriminant < 0)
    {
        obj->t = -1;
        return (false);
    }
    
    //Calculate the two possible t values
    if (discriminant >= 0)
    {
        obj->t = (-b - sqrt(discriminant)) / (2 * a);
        obj->t2 = (-b + sqrt(discriminant)) /(2 * a);
    }
    // m is a scalar that determines the closet point on the axis to the hit point.
    float m1 = dot(ray->dir,obj->vec2) * obj->t + dot(sub(ray->orig,obj->vec), obj->vec2);
    float m2 = dot(ray->dir,obj->vec2) * obj->t2 + dot(sub(ray->orig,obj->vec), obj->vec2);
    
    //Check if the intersection point is within the height on the cylinder
    if (obj->t > obj->t2)
    {
        float t = obj->t;
        obj->t = obj->t2;
        obj->t2 = t;
    }
    if (obj->t < 0 )
    {
        obj->t = -1;
        return (false);
    }
    if( (m1 <= obj->cyl_height && m1 >= -obj->cyl_height) ||(m2 <= obj->cyl_height && m2 >= -obj->cyl_height))
    {
       return (true);
    }
    obj->t = -1;
    return (true);//not intersects
}

bool	hit_cylinder(t_object *obj, t_ray *ray)
{
	float t;
    
	hit_cylinder_caps(obj,ray);
	t = obj->t;
	hit_cylinder_body(obj,ray);
	if (obj->t >= 0 && t >= 0)
	{
		if (obj->t > t)
			obj->t = t;
	}
	if (obj->t < 0)
		obj->t = t;
   return(false);
}