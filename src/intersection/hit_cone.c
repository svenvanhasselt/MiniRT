/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cone.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 10:25:21 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/19 17:30:55 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	hit_cone(t_object *obj, t_ray *ray)
{
    float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t;
	float	t2;
	float	tana;
	t_vec	oc;

	t = -1;
	t2 = -1;
	oc = sub(ray->orig,obj->vec);
	tana = tan(45.0/180.0*3.141);
	a = dot(ray->dir,ray->dir) - (1 + tana * tana)*pow(dot(ray->dir, obj->vec2),2);
	b = 2*(dot(ray->dir, oc) - (1 + tana * tana)*dot(ray->dir, obj->vec2) * dot(oc, obj->vec2));
	c = dot(oc, oc) - (1 + tana * tana)*pow(dot(oc, obj->vec2), 2) ;

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
		t = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) /(2 * a);
	}
	
	float m1 = dot(ray->dir,obj->vec2) * t + dot(sub(ray->orig,obj->vec), obj->vec2);
	float m2 = dot(ray->dir,obj->vec2) * t2 + dot(sub(ray->orig,obj->vec), obj->vec2);
	obj->t = compare_t(t, t2);

	//Check if the intersection point is within the height on the cylinder
	if( (m1 <= obj->height / 2 && m1 >= -obj->height / 2) || (m2 <= obj->height / 2 && m2 >= -obj->height / 2 ))
		return (true);
	obj->t = -1;
	return (false);
}
