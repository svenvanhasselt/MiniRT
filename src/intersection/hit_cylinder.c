/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 16:47:30 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/13 14:09:13 by yizhang       ########   odam.nl         */
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

float	hit_cylinder_body(t_object *obj, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t;
	float	t2;
	t_vec	oc;

	t = -1;
	t2 = -1;
	printf("x:%f y:%f z:%f\n", obj->vec2.x, obj->vec2.y,obj->vec2.z);//vec don't have negative number
	oc = sub(ray->orig,obj->vec);//subtract the center of the cylinder from the ray origin to turn the problem into a (0,0,0) coordinate
	a = dot(ray->dir,ray->dir) - pow(dot(ray->dir, obj->vec2),2);
	b = 2*(dot(ray->dir, oc) - dot(ray->dir, obj->vec2) * dot(oc, obj->vec2));
	c = dot(oc, oc) - pow(dot(oc, obj->vec2), 2) - pow(obj->cyl_diameter / 2, 2);
	
	//Calculate the discriminant
	discriminant = b*b - 4*a*c;
	if (discriminant < 0)
		return (-1);
	//Calculate the two possible t values
	if (discriminant >= 0)
	{
		t = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) /(2 * a);
	}
	
	// m is a scalar that determines the closet point on the axis to the hit point.
	float m1 = dot(ray->dir,obj->vec2) * t + dot(sub(ray->orig,obj->vec), obj->vec2);
	float m2 = dot(ray->dir,obj->vec2) * t2 + dot(sub(ray->orig,obj->vec), obj->vec2);
	t = compare_t(t, t2);

	//Check if the intersection point is within the height on the cylinder
	if( (m1 <= obj->cyl_height / 2 && m1 >= -obj->cyl_height / 2) || (m2 <= obj->cyl_height / 2 && m2 >= -obj->cyl_height / 2 ))
		return (t);
	return (-1);//not intersects
}

bool	hit_cylinder(t_object *obj, t_ray *ray)
{
	float	t;
	float	t2;
	
	t = hit_cylinder_caps(obj,ray);
	t2 = hit_cylinder_body(obj,ray);
	obj->t = compare_t(t, t2);
	if (obj->t > 0)
		return (true);
	return(false);
}